hebrewToGregorian(int y, int m, int d)
{
    static class h_date h;
    int s;

    y -= 3744;
    s = hebrewDaysElapsed(y);
    d += s;
    s = hebrewDaysElapsed(y + 1) - s;

    if (s > 365 && m > 6) {
        --m;
        d += 30;
    }
    d += (59 * (m - 1) + 1) / 2;

    if (s % 10 > 4 && m > 2) {
        d++;
    }
    if (s % 10 < 4 && m > 3) {
        d--;
    }


    d -= 6002;

    y = (d + 36525) * 4 / 146097 - 1;
    d -= y / 4 * 146097 + (y % 4) * 36524;
    y *= 100;


    s = (d + 366) * 4 / 1461 - 1;
    d -= s / 4 * 1461 + (s % 4) * 365;
    y += s;

    m = (d + 245) * 12 / 367 - 7;
    d -= m * 367 / 12 - 30;
    if (++m >= 12) {
        m -= 12;
        y++;
    }
    h.hd_day = d;
    h.hd_mon = m;
    h.hd_year = y;
    return(&h);
}
