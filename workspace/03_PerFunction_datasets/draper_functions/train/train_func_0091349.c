stringVectorToString(const MSStringVector& aVector_)
{
  MSString aString;
  unsigned i=0;
  if (aVector_.length()>0)
   {
     for (;i<aVector_.length()-1;i++) aString<<aVector_(i)<<"\\n";
     aString<<aVector_(i);
   }
  return aString;
}
