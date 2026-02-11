make_rfc822_date_string(struct tm *tm, int yyyy, int use_gmt)
{
  int st;
  char *buf;

  if (tm == NULL) {
	time_t now;

	time(&now);
	if (use_gmt)
	  tm = gmtime(&now);
	else
	  tm = localtime(&now);
  }

  buf = (char *) malloc(64);
  if (yyyy) {
	if (use_gmt)
	  st = strftime(buf, 64, "%a, %d %b %Y %H:%M:%S GMT", tm);
	else
	  st = strftime(buf, 64, "%a, %d %b %Y %H:%M:%S %z (%Z)", tm);
  }
  else {
	if (use_gmt)
	  st = strftime(buf, 64, "%a, %d %b %y %H:%M:%S GMT", tm);
	else
	  st = strftime(buf, 64, "%a, %d %b %Y %H:%M:%S %z (%Z)", tm);
  }

  if (st == 0 || st == 64) {


	return("Mon, 1-Jan-2001 8:00:00 GMT");
  }

  return(buf);
}
