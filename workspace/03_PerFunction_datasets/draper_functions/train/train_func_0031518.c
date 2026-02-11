GetAsWorld() const
{
  double result;
  result = setAsPercent_ ? value_*(max_-min_)/100.0 : value_;
  return std::min(fabs(max_-min_),std::max(0.0,result));
}
