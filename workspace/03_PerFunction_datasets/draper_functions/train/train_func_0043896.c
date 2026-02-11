julianDayToDate(int jd, int &year, int &month, int &day) const
{


    int a = jd + 32044;
    int b = ((4 * a) + 3) / 146097;
    int c = a - ((146097 * b) / 4);
    int d = ((4 * c) + 3) / 1461;
    int e = c - ((1461 * d) / 4);
    int m = ((5 * e) + 2) / 153;
    day = e - (((153 * m) + 2) / 5) + 1;
    month = m + 3 - (12 * (m / 10));
    year = (100 * b) + d - 4800 + (m / 10);


    if (year < 1) {
        year = year - 1;
    }

    return true;
}
