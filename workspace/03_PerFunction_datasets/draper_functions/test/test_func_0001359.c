ITMtoDeg (char *zone, double x, double y, double *lat, double *lon)
{
  int n;


  if (strcmp (zone, "--") == 0 || x < 0.0 || x > 100000.0 || y < 0.0 ||
      y > 100000.0)
    {
      *lat = 0.0;
      *lon = 0.0;
      return;
    }

  n = strchr (zoneID, zone[1]) - zoneID;

  x += (n % 5) * 100000.0 - 200000.0;
  y += (n / 5) * 100000.0 - 250000.0;

  fromTM (x, y, lat0, lon0, k0, lat, lon);
}
