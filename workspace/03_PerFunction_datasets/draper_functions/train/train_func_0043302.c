point_n(uint32 num, String *result) const
{
  uint32 n_points;
  if (no_data(m_data, 4))
    return 1;
  n_points= uint4korr(m_data);
  if ((uint32) (num - 1) >= n_points)
    return 1;

  return create_point(result, m_data + 4 + (num - 1) * POINT_DATA_SIZE);
}
