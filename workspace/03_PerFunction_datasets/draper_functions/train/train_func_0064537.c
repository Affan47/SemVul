get_data_as_wkt(String *txt, const char **end) const
{
  uint32 n_linear_rings;
  const char *data= m_data;

  if (no_data(data, 4))
    return 1;

  n_linear_rings= uint4korr(data);
  data+= 4;

  while (n_linear_rings--)
  {
    uint32 n_points;
    if (no_data(data, 4))
      return 1;
    n_points= uint4korr(data);
    data+= 4;

    if (not_enough_points(data, n_points) ||
	txt->reserve(2 + ((MAX_DIGITS_IN_DOUBLE + 1) * 2 + 1) * n_points))
      return 1;
    txt->qs_append('(');
    data= append_points(txt, n_points, data, 0);
    (*txt) [txt->length() - 1]= ')';
    txt->qs_append(',');
  }
  txt->length(txt->length() - 1);
  *end= data;
  return 0;
}
