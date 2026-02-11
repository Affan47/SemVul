min_of_the_max_uint(
                       uint (handler::*operator_func)(void) const) const
{
  handler **file;
  uint min_of_the_max= ((*m_file)->*operator_func)();

  for (file= m_file+1; *file; file++)
  {
    uint tmp= ((*file)->*operator_func)();
    set_if_smaller(min_of_the_max, tmp);
  }
  return min_of_the_max;
}
