makeFromDays(int i_)
{

  if (i_<0) i_=-i_;
  _years=double(i_)/daysInYear();
}
