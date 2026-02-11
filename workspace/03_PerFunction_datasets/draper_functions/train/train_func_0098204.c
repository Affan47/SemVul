cyrus_ctime(time_t date, char *datebuf)
{
    struct tm *tm = localtime(&date);
    long gmtoff = gmtoff_of(tm, date);
    int gmtnegative = 0;
    static const char *monthname[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    if (date == 0 || tm->tm_year < 69) {
	abort();
    }

    if (gmtoff < 0) {
	gmtoff = -gmtoff;
	gmtnegative = 1;
    }
    gmtoff /= 60;
    sprintf(datebuf,
	    "%2u-%s-%u %.2u:%.2u:%.2u %c%.2lu%.2lu",
	    tm->tm_mday, monthname[tm->tm_mon], tm->tm_year+1900,
	    tm->tm_hour, tm->tm_min, tm->tm_sec,
	    gmtnegative ? '-' : '+', gmtoff/60, gmtoff%60);
}
