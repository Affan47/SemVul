getNumberOfVariables()const
{
  TermMap::const_iterator i=terms.begin();
  if(i==terms.end())return 0;

  return i->first.exponent.size();
}
