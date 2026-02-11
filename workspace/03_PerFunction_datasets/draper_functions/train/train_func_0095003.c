mag_trkparse(char* trkmsg)
{
  double latdeg, lngdeg;
  int alt;
  char altunits;
  char lngdir, latdir;
  int dmy;
  int hms;
  int fracsecs;
  struct tm tm;
  waypoint* waypt;

  waypt  = waypt_new();

  memset(&tm, 0, sizeof(tm));


  parse_istring(trkmsg);
  latdeg = atof(ifield[1]);
  latdir = ifield[2][0];
  lngdeg = atof(ifield[3]);
  lngdir = ifield[4][0];
  alt = atof(ifield[5]);
  altunits = ifield[6][0];
  sscanf(ifield[7], "%d.%d", &hms, &fracsecs);


  dmy = atoi(ifield[10]);

  tm.tm_sec = hms % 100;
  hms = hms / 100;
  tm.tm_min = hms % 100;
  hms = hms / 100;
  tm.tm_hour = hms % 100;

  tm.tm_year = 100 + dmy % 100;
  dmy = dmy / 100;
  tm.tm_mon =  dmy % 100 - 1;
  dmy = dmy / 100;
  tm.tm_mday = dmy % 100;

  waypt->creation_time = mkgmtime(&tm);
  waypt->microseconds = CENTI_TO_MICRO(fracsecs);

  if (latdir == 'S') {
    latdeg = -latdeg;
  }
  waypt->latitude = ddmm2degrees(latdeg);

  if (lngdir == 'W') {
    lngdeg = -lngdeg;
  }
  waypt->longitude = ddmm2degrees(lngdeg);

  waypt->altitude = alt;

  return waypt;

}
