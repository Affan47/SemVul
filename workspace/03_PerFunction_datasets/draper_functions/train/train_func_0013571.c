rs_above_integer(const double value) const
{
  double value2=floor(value);
  double value3=rs2round(value);
  if (fabs(value3-value)< param.getEPS() * (fabs(value3)+1.0))
    return 0.0;
  return value-value2;
}
