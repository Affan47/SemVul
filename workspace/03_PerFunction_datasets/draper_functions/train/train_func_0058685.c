enumToString(unsigned long enumValue_, const MSStringVector& values_,
				   const MSUnsignedLongVector& enumValues_,
				   const MSString& empty_, MSBoolean exact_)
{
  MSString aString;
  int i,n=enumValues_.length();
  for(i=0;i<n;i++)
   {
     if(exact_==MSTrue)
      {
       if(enumValue_==enumValues_(i))
	{
	  aString=values_(i);
	  break;
	}
      }
     else
      {
        if(enumValue_&enumValues_(i))
	 {
	   if (aString.length()!=0)	aString<<'|';
	   aString<<values_(i);
	 }
      }
   }
  if(aString.length()==0) aString=empty_;
  return aString;
}
