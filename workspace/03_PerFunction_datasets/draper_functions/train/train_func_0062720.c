sod(struct tm *tmptr, unsigned y, unsigned m, unsigned d)
{
	struct tm mytm;
	time_t tt;


	mytm= *tmptr;
	mytm.tm_year=y-1900;
	mytm.tm_mon=m-1;
	mytm.tm_mday=d;
	mytm.tm_hour=0;
	mytm.tm_min=0;
	mytm.tm_sec=0;

	tt=mktime(&mytm);

	if (tt == (time_t)-1 ||
	    (tmptr=localtime(&tt)) == NULL)
		return (0);


	mytm= *tmptr;
	mytm.tm_year=y-1900;
	mytm.tm_mon=m-1;
	mytm.tm_mday=d;
	mytm.tm_hour=0;
	mytm.tm_min=0;
	mytm.tm_sec=0;

	tt=mktime(&mytm);

	if (tt == (time_t)-1)
		return (0);
	return (tt);
}
