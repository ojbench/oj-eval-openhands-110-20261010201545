#include <bits/stdc++.h>
using namespace std;

static const int DAYS_IN_MONTH[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeap(int y){
    return (y%400==0) || (y%4==0 && y%100!=0);
}

int daysInMonth(int y,int m){
    if(m==2) return DAYS_IN_MONTH[m] + (isLeap(y)?1:0);
    return DAYS_IN_MONTH[m];
}

// days since 1900-01-01 (day 0)
long long dateToDays(int y,int m,int d){
    long long days=0;
    for(int year=1900; year<y; ++year){
        days += 365 + (isLeap(year)?1:0);
    }
    for(int month=1; month<m; ++month){
        days += daysInMonth(y, month);
    }
    days += d-1; // because 1900-01-01 is day 0
    return days;
}

void daysToDate(long long days,int &y,int &m,int &d){
    y=1900;
    while(true){
        int yearDays = 365 + (isLeap(y)?1:0);
        if(days>=yearDays){
            days -= yearDays;
            ++y;
        }else break;
    }
    m=1;
    while(true){
        int dim = daysInMonth(y,m);
        if(days>=dim){
            days -= dim;
            ++m;
        }else break;
    }
    d = (int)days + 1;
}

class Date{
private:
    int _year,_month,_day;
    long long _days; // days since epoch
    void updateFromDays(){
        daysToDate(_days,_year,_month,_day);
    }
    void recompute(){
        _days = dateToDays(_year,_month,_day);
    }
    bool valid(int y,int m,int d){
        if(y<1900||y>2030) return false;
        if(m<1||m>12) return false;
        if(d<1||d>daysInMonth(y,m)) return false;
        return true;
    }
public:
    Date():_year(1900),_month(1),_day(1){ recompute(); }
    Date(int y,int m,int d){
        if(valid(y,m,d)){
            _year=y;_month=m;_day=d; recompute();
        }else{
            _year=1900;_month=1;_day=1; recompute();
        }
    }
    // prefix ++
    Date& operator++(){
        ++_days; updateFromDays();
        return *this;
    }
    // postfix ++
    Date operator++(int){
        Date tmp=*this; ++(*this); return tmp;
    }
    // prefix --
    Date& operator--(){
        --_days; updateFromDays();
        return *this;
    }
    // postfix --
    Date operator--(int){
        Date tmp=*this; --(*this); return tmp;
    }
    // + days
    Date operator+(int d) const{
        Date res=*this; res._days += d; res.updateFromDays(); return res;
    }
    // - days
    Date operator-(int d) const{
        Date res=*this; res._days -= d; res.updateFromDays(); return res;
    }
    // date - date => absolute days
    long long operator-(const Date& other) const{
        long long diff = _days - other._days;
        return diff>=0? diff : -diff;
    }
    // less than
    bool operator<(const Date& other) const{
        if(_year!=other._year) return _year<other._year;
        if(_month!=other._month) return _month<other._month;
        return _day<other._day;
    }
    // output
    friend ostream& operator<<(ostream& os, const Date& dt){
        os<<dt._year<<"-"<<dt._month<<"-"<<dt._day;
        return os;
    }
    void out() const{
        cout<<_year<<"-"<<_month<<"-"<<_day<<"\n";
    }
};

void Test(){
    int op;cin>>op;
    int yy,mm,dd;
    if(op==1||op==0){
        Date d0; // default 1900-1-1
        Date d1(2000,2,29);
        Date d2(1900,2,29);
        cout<<d0<<"\n"<<d1<<"\n"<<d2<<"\n";
    }
    if(op==2||op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<"\n";
        for(int i=0;i<5;++i) cout<<d0++<<"\n";
        for(int i=0;i<5;++i) cout<<d0--<<"\n";
        for(int i=0;i<2;++i) cout<<--d0<<"\n";
        cout<<d0<<"\n";
    }
    if(op==3||op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        cout<<d0+100<<"\n";
        cout<<d0-1000<<"\n";
    }
    if(op==4||op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1)<<"\n";
    }
    if(op==5||op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<d0-d1<<"\n";
    }
}

int main(){
    Test();
    return 0;
}
