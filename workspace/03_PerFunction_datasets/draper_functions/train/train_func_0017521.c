icaltimezone_parse_zone_tab		(void)
{
    char *filename;
    FILE *fp;
    char buf[1024];
    char location[1024];
    unsigned int filename_len;
    int latitude_degrees = 0, latitude_minutes = 0, latitude_seconds = 0;
    int longitude_degrees = 0, longitude_minutes = 0, longitude_seconds = 0;
    icaltimezone zone;

    icalerror_assert (builtin_timezones == NULL,
		      "Parsing zones.tab file multiple times");

    builtin_timezones = icalarray_new (sizeof (icaltimezone), 32);

#ifndef USE_BUILTIN_TZDATA
    filename_len = strlen ((char *) icaltzutil_get_zone_directory()) + strlen (ZONES_TAB_SYSTEM_FILENAME)
	+ 2;
#else
    filename_len = strlen (get_zone_directory()) + strlen (ZONES_TAB_FILENAME)
	+ 2;
#endif

    filename = (char*) malloc (filename_len);
    if (!filename) {
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return;
    }
#ifndef USE_BUILTIN_TZDATA
    snprintf (filename, filename_len, "%s/%s", icaltzutil_get_zone_directory (),
	      ZONES_TAB_SYSTEM_FILENAME);
#else
    snprintf (filename, filename_len, "%s/%s", get_zone_directory(),
	      ZONES_TAB_FILENAME);
#endif

    fp = fopen (filename, "r");
    free (filename);
    if (!fp) {
	icalerror_set_errno(ICAL_FILE_ERROR);
	return;
    }

    while (fgets (buf, sizeof(buf), fp)) {
	if (*buf == '#') continue;

#ifdef USE_BUILTIN_TZDATA

	if (sscanf (buf, "%4d%2d%2d %4d%2d%2d %s",
		    &latitude_degrees, &latitude_minutes,
		    &latitude_seconds,
		    &longitude_degrees, &longitude_minutes,
		    &longitude_seconds,
		    location) != 7) {
	    fprintf (stderr, "Invalid timezone description line: %s\n", buf);
	    continue;
	}
#else
	if (fetch_lat_long_from_string (buf, &latitude_degrees, &latitude_minutes,
				&latitude_seconds,
				&longitude_degrees, &longitude_minutes, &longitude_seconds,
				location)) {
	    fprintf (stderr, "Invalid timezone description line: %s\n", buf);
	    continue;
	}
#endif

	icaltimezone_init (&zone);
	zone.location = strdup (location);

	if (latitude_degrees >= 0)
	    zone.latitude = (double) latitude_degrees
		+ (double) latitude_minutes / 60
		+ (double) latitude_seconds / 3600;
	else
	    zone.latitude = (double) latitude_degrees
		- (double) latitude_minutes / 60
		- (double) latitude_seconds / 3600;

	if (longitude_degrees >= 0)
	    zone.longitude = (double) longitude_degrees
		+ (double) longitude_minutes / 60
		+ (double) longitude_seconds / 3600;
	else
	    zone.longitude = (double) longitude_degrees
		- (double) longitude_minutes / 60
		- (double) longitude_seconds / 3600;

	icalarray_append (builtin_timezones, &zone);

#if 0
	printf ("Found zone: %s %f %f\n",
		location, zone.latitude, zone.longitude);
#endif
    }

    fclose (fp);
}
