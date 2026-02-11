GetAsPercent() const
{
  double result;
  result = setAsPercent_ ? value_ : value_/(max_-min_)*100.0;
  return std::min(100.0,std::max(0.0,result));
}
