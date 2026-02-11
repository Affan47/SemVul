GetNiceNumber( double d )
{
  int width = 10;
  int precision = 3;
  std::stringstream ss;
  std::string s;
  if( fabs(d)>=1000.0 || fabs(d)<=0.01 )
  {
    ss << std::setw(width) << std::setprecision(precision) << std::scientific << d;
  }
  else
  {
    if( fabs(d) < 10.0 )
    {
      width = 6;
      precision = 3;
    }
    else if( fabs(d) < 100.0 )
    {
      width = 6;
      precision = 2;
    }
    else if( fabs(d) < 1000.0 )
    {
      width = 6;
      precision = 1;
    }
    ss << std::setw(width) << std::setprecision(precision) << std::fixed << d;
  }
  ss >> s;
  if( d >= 0.0 )s = std::string(" ")+s;
  return wxString( s.c_str(), wxConvUTF8 );
}
