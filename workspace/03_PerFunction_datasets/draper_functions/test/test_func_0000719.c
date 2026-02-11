icaltimezone_load_builtin_timezone	(icaltimezone *zone)
{
    icalcomponent *subcomp;


    if (!zone->location || !zone->location[0])
	return;

#ifdef USE_BUILTIN_TZDATA
    {
    char *filename;
    icalcomponent *comp;
    unsigned int filename_len;
    FILE *fp;
    icalparser *parser;

    filename_len = strlen (get_zone_directory()) + strlen (zone->location) + 6;

    filename = (char*) malloc (filename_len);
    if (!filename) {
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return;
    }

    snprintf (filename, filename_len, "%s/%s.ics", get_zone_directory(),
	      zone->location);

    fp = fopen (filename, "r");
    free (filename);
    if (!fp) {
	icalerror_set_errno(ICAL_FILE_ERROR);
	return;
    }


    parser = icalparser_new ();
	icalparser_set_gen_data (parser, fp);
	comp = icalparser_parse (parser, icaltimezone_load_get_line_fn);
    icalparser_free (parser);
	fclose (fp);


    subcomp = icalcomponent_get_first_component (comp,
						 ICAL_VTIMEZONE_COMPONENT);
#else
	subcomp = icaltzutil_fetch_timezone (zone->location);
#endif

    if (!subcomp) {
	icalerror_set_errno(ICAL_PARSE_ERROR);
	return;
    }

    icaltimezone_get_vtimezone_properties (zone, subcomp);

#ifdef USE_BUILTIN_TZDATA
    icalcomponent_remove_component(comp,subcomp);
    icalcomponent_free(comp);
    }
#endif

}
