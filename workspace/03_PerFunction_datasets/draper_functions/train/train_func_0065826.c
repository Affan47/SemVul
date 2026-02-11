xol_waypt(const char *args, const char **attrv)
{
  const char **avp = &attrv[0];
  int x=0, y=0;

  while (*avp) {
    if (strcmp(avp[0], "y") == 0) {
      y = atoi(avp[1]);
    } else if (strcmp(avp[0], "x") == 0) {
      x = atoi(avp[1]);
    }
    avp+=2;
  }

  GPS_Math_Swiss_EN_To_WGS84((double)x, (double)y, &wpt->latitude, &wpt->longitude);
}
