homogenization(PolynomialRing const &newRing, IntegerVector const *w)const
{
  PolynomialSet ret(newRing);
  for(const_iterator i=begin();i!=end();i++)
    ret.push_back(i->homogenization(newRing,w));

  return ret;
}
