create_point(String *result, double x, double y) const
{
  if (result->reserve(1 + 4 + SIZEOF_STORED_DOUBLE * 2))
    return 1;

  result->q_append((char) wkb_ndr);
  result->q_append((uint32) wkb_point);
  result->q_append(x);
  result->q_append(y);
  return 0;
}
