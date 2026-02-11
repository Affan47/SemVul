makeday(int imonth,int iday,int iyear)
{
    struct disc_time funkychickens;

    int cal[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int dayspast=0;

    memset(&funkychickens,0,sizeof(funkychickens));

    if (imonth < 1 || imonth > 12) {
	    funkychickens.season = -1;
	    return funkychickens;
    }
    if (iday < 1 || iday > cal[imonth-1]) {
	    if (!(imonth == 2 && iday == 29 && iyear%4 == 0 &&
		  (iyear%100 != 0 || iyear%400 == 0))) {
		    funkychickens.season = -1;
		    return funkychickens;
	    }
    }

    imonth--;
    funkychickens.year= iyear+1166;
    while(imonth>0) { dayspast+=cal[--imonth]; }
    funkychickens.day=dayspast+iday-1;
    funkychickens.season=0;
    if((funkychickens.year%4)==2) {
	if (funkychickens.day==59 && iday==29)  funkychickens.day=-1;
    }
    funkychickens.yday=funkychickens.day;

    while(funkychickens.day>=73) {
	funkychickens.season++;
	funkychickens.day-=73;
    }
    return funkychickens;
}
