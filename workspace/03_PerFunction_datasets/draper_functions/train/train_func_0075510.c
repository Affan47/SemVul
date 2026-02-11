get_area(int *prefix, RATE *Rate, char *number,
                    char **msg, char *message) {
  int r, ret, p, ret1;
  REDIRZ rz;
  TELNUM num, onum;
  int oprefix = *prefix;
  int area, zone;

  rz.start_zone=0;
  rz.end_zone=9999;
  number=strcat3(Rate->dst);
  if (Rate->_area==UNKNOWN) {
    if (*Rate->dst[0]) {
      if(getDest(number, &onum))
        *onum.keys = '\0';
      normalizeNumber(number, &onum, TN_PROVIDER | TN_NOCLEAR);
    }
  }
  num = onum;
  ret = get_area1(oprefix, Rate, number, &num, 0, &rz);
  area = Rate->_area;
  zone = Rate->_zone;
  if (Provider[oprefix].nRedir) {
    for(r = 0; r<Provider[oprefix].nRedir; r++) {
      p = Provider[oprefix].Redir[r].p._prefix;
      num = onum;
      Rate->_area = Rate->_zone = UNKNOWN;
      ret1 = get_area1(p, Rate, number, &num, ret, &Provider[oprefix].Redir[r]);
      if(ret1 > ret) {
        ret = ret1;
	*prefix = p;
        area = Rate->_area;
        zone = Rate->_zone;
      }
    }
  }
  Rate->_area = area;
  Rate->_zone = zone;

  if (Rate->_area<0) {
    Rate->_area = UNKNOWN;
    if (msg) snprintf (message, LENGTH,
      	"No area info for provider %s, destination %s",	epnum(oprefix), number);
    Rate->_zone=UNZONE;
    ret= UNKNOWN;
  }
  return ret;
}
