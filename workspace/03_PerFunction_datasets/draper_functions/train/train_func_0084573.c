gregorian_cal_to_jul(int y, int m, int d)
{
    long c;


    c = (long) ((y - 1)/100);
    return (1461L*(y - 1))/4 + c/4 - c
        + (m*489)/16 - ((m > 2) ? (gregorian_non_leap(y) ? 32L : 31L) : 30L)
        + d + 1721425L;

}
