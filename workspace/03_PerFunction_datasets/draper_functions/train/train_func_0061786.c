time2generalizedtime (time_t t, octet_string *s)
{
     struct tm *tm;
     size_t len;

     len = 15;

     s->data = malloc(len + 1);
     if (s->data == NULL)
	 return ENOMEM;
     s->length = len;
     tm = gmtime (&t);
     snprintf (s->data, len + 1, "%04d%02d%02d%02d%02d%02dZ",
	       tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	       tm->tm_hour, tm->tm_min, tm->tm_sec);
     return 0;
}
