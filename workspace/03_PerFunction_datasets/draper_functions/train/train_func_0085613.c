getFramerate()
{
  return (s_deltime != 0.0) ? (1000. / s_deltime) : 0.0;
}
