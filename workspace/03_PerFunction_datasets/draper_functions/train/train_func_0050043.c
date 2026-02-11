gpx_write(void)
{
  time_t now = 0;
  int short_length;


  if (! gpx_wversion) {
    if (! gpx_version) {
      gpx_wversion = (char *)"1.0";
    } else {
      gpx_wversion = (char *)gpx_version;
    }
  }

  if (opt_humminbirdext || opt_garminext) {
    gpx_wversion = (char*)"1.1";
  }

  gpx_wversion_num = strtod(gpx_wversion, NULL) * 10;

  if (gpx_wversion_num <= 0) {
    fatal(MYNAME ": gpx version number of '%s' not valid.\n", gpx_wversion);
  }

  now = current_time();

  short_length = atoi(snlen);

  if (suppresswhite) {
    setshort_whitespace_ok(mkshort_handle, 0);
  }

  setshort_length(mkshort_handle, short_length);

  gbfprintf(ofd, "<?xml version=\"1.0\" encoding=\"%s\"?>\n", global_opts.charset_name);
  gbfprintf(ofd, "<gpx\n  version=\"%s\"\n", gpx_wversion);
  gbfprintf(ofd, "  creator=\"" CREATOR_NAME_URL "\"\n");
  gbfprintf(ofd, "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");

  if (opt_humminbirdext) {
    gbfprintf(ofd, "  xmlns:h=\"http://humminbird.com\"\n");
  }
  if (opt_garminext)
    gbfprintf(ofd, "  xmlns:gpxx=\"http://www.garmin.com/xmlschemas/GpxExtensions/v3\"\n"
              "  xmlns:gpxtpx=\"http://www.garmin.com/xmlschemas/TrackPointExtension/v1\"\n");

  gbfprintf(ofd, "  xmlns=\"http://www.topografix.com/GPX/%c/%c\"\n", gpx_wversion[0], gpx_wversion[2]);
  if (xsi_schema_loc) {
    gbfprintf(ofd, "  xsi:schemaLocation=\"%s\">\n", xsi_schema_loc);
  } else {
    gbfprintf(ofd,
              "  xsi:schemaLocation=" DEFAULT_XSI_SCHEMA_LOC_FMT">\n",
              gpx_wversion[0], gpx_wversion[2],
              gpx_wversion[0], gpx_wversion[2]);
  }

  if (gpx_wversion_num > 10) {
    gbfprintf(ofd, "<metadata>\n");
  }
  gpx_write_gdata(&gpx_global->name, "name");
  gpx_write_gdata(&gpx_global->desc, "desc");


  if (gpx_wversion_num < 11) {
    gpx_write_gdata(&gpx_global->author, "author");
  }

  if (gpx_wversion_num < 11) {
    gpx_write_gdata(&gpx_global->email, "email");
    gpx_write_gdata(&gpx_global->url, "url");
    gpx_write_gdata(&gpx_global->urlname, "urlname");
  }
  xml_write_time(ofd, now, 0, "time");
  gpx_write_gdata(&gpx_global->keywords, "keywords");

  gpx_write_bounds();

  if (gpx_wversion_num > 10) {
    gbfprintf(ofd, "</metadata>\n");
  }

  waypt_disp_all(gpx_waypt_pr);
  gpx_route_pr();
  gpx_track_pr();

  gbfprintf(ofd, "</gpx>\n");
}
