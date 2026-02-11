fmt_setunits(fmt_units u)
{
  switch (u) {
  case units_statute:
  case units_metric:
  case units_nautical:
  case units_aviation:
    units = u;
    return 0;
  default:
    return 1;
  }
}
