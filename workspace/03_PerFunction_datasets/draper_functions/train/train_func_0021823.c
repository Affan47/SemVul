_embryo_time_date(Embryo_Program *ep, Embryo_Cell *params)
{
   static time_t       last_tzset = 0;
   struct timeval      timev;
   struct tm          *tm;
   time_t              tt;

   if (params[0] != (8 * sizeof(Embryo_Cell))) return 0;
   gettimeofday(&timev, NULL);
   tt = (time_t)(timev.tv_sec);
   if ((tt > (last_tzset + 1)) ||
       (tt < (last_tzset - 1)))
     {
	last_tzset = tt;
	tzset();
     }
   tm = localtime(&tt);
   if (tm)
     {
	Embryo_Cell *cptr;
	double t;
	float  f;

	cptr = embryo_data_address_get(ep, params[1]);
	if (cptr) *cptr = tm->tm_year + 1900;
	cptr = embryo_data_address_get(ep, params[2]);
	if (cptr) *cptr = tm->tm_mon + 1;
	cptr = embryo_data_address_get(ep, params[3]);
	if (cptr) *cptr = tm->tm_mday;
	cptr = embryo_data_address_get(ep, params[4]);
	if (cptr) *cptr = tm->tm_yday;
	cptr = embryo_data_address_get(ep, params[5]);
	if (cptr) *cptr = (tm->tm_wday + 6) % 7;
	cptr = embryo_data_address_get(ep, params[6]);
	if (cptr) *cptr = tm->tm_hour;
	cptr = embryo_data_address_get(ep, params[7]);
	if (cptr) *cptr = tm->tm_min;
	cptr = embryo_data_address_get(ep, params[8]);
	t = (double)tm->tm_sec + (((double)timev.tv_usec) / 1000000);
	f = (float)t;
	if (cptr) *cptr = EMBRYO_FLOAT_TO_CELL(f);

     }
   return 0;
}
