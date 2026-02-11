init_from_wkb(const char *wkb, uint len,
                              wkbByteOrder bo, String *res)
{
  double x, y;
  if (len < POINT_DATA_SIZE || res->reserve(POINT_DATA_SIZE))
    return 0;
  x= wkb_get_double(wkb, bo);
  y= wkb_get_double(wkb + SIZEOF_STORED_DOUBLE, bo);
  res->q_append(x);
  res->q_append(y);
  return POINT_DATA_SIZE;
}
