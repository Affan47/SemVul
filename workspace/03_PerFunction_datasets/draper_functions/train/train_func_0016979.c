routesimple_init(const char *args)
{
  count = 0;

  if (!!countopt == !!erroropt) {
    fatal(MYNAME ": You must specify either count or error, but not both.\n");
  }
  if ((!!xteopt + !!lenopt + !!relopt) > 1) {
    fatal(MYNAME ": You may specify only one of crosstrack, length, or relative.\n");
  }
  if (!xteopt && !lenopt && !relopt) {
    xteopt = "";
  }

  if (countopt) {
    count = atol(countopt);
  }
  if (erroropt) {
    int res = parse_distance(erroropt, &error, 1.0, MYNAME);
    if (res == 0) {
      error = 0;
    } else if (res == 2) {
      error = METERS_TO_MILES(error);
    }
  }
}
