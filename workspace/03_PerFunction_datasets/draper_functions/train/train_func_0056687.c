is_a_power_of_2(unsigned int fac) const
{
  if (fac >= 1) return(is_a_power_of_2(double(fac)));
  else return(false);
}
