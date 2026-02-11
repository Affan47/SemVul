dateToJD(DDouble &jd, DLong &day, DLong &month, DLong &year, DLong &hour, DLong &minute, DDouble &second)
  {
    if (year < -4716 || year > 5000000 || year==0 ) return false;
    if (month < 1 || month > 12) return false;
    if (day < 0 || day > 31) return false;


    DDouble a,y,b,c;
    DLong m;
    y=(year>0)?year:year+1;

    m=month;
    b=0.0;
    c=0.0;
    if (month <= 2)
    {
      y=y-1.0;
      m=m+12;
    }
    if (y < 0)
    {
      c=-0.75;
    } else {
       if (year > 1582  ||  (year == 1582 &&  (month > 10  ||
               (month == 10 && day > 14)))) {
          a=floor(y/100.0);
          b=2.0-a+floor(a/4.0);
       } else if (year == 1582 && month == 10 && day >= 5 && day <= 14) {
          jd= 2299161;
          return true;
       }
    }
    jd=ceil(365.25*y+c)+floor(30.6001*(m+1))+day+(hour*1.0)/24.0+(minute*1.0)/1440.0+
    (second*1.0)/86400.0+1720994.50+b;
    if (y > 0) jd--;

    return true;
  }
