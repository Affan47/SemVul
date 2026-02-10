ISO2UNIX(char *timestring) {
char c, *p;
struct tm	when;
time_t		t;


	t = time(NULL);
	localtime_r(&t, &when);
	when.tm_sec  = 0;
	when.tm_wday = 0;
	when.tm_yday = 0;
	when.tm_isdst = -1;

	if ( strlen(timestring) != 12 ) {
		LogError( "Wrong time format '%s'\n", timestring);
		return 0;
	}


	p = timestring;
	c = p[4];
	p[4] = '\0';
	when.tm_year = atoi(p) - 1900;
	p[4] = c;


	p += 4;
	c = p[2];
	p[2] = '\0';
	when.tm_mon = atoi(p) - 1;
	p[2] = c;


	p += 2;
	c = p[2];
	p[2] = '\0';
	when.tm_mday = atoi(p);
	p[2] = c;


	p += 2;
	c = p[2];
	p[2] = '\0';
	when.tm_hour = atoi(p);
	p[2] = c;


	p += 2;
	when.tm_min = atoi(p);

	t = mktime(&when);
	if ( t == -1 ) {
		LogError( "Failed to convert string '%s'\n", timestring);
		return 0;
	} else {

		return t;
	}

}
