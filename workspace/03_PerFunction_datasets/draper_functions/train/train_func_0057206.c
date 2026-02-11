geom_length(double *len) const
{
  uint32 n_points;
  double prev_x, prev_y;
  const char *data= m_data;

  *len= 0;
  if (no_data(data, 4))
    return 1;
  n_points= uint4korr(data);
  data+= 4;
  if (n_points < 1 || not_enough_points(data, n_points))
    return 1;

  get_point(&prev_x, &prev_y, data);
  data+= SIZEOF_STORED_DOUBLE*2;

  while (--n_points)
  {
    double x, y;
    get_point(&x, &y, data);
    data+= SIZEOF_STORED_DOUBLE * 2;
    *len+= sqrt(pow(prev_x-x,2)+pow(prev_y-y,2));
    prev_x= x;
    prev_y= y;
  }
  return 0;
}
