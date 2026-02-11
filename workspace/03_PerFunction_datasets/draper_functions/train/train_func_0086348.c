headingWidth(void) const
{
  unsigned n=heading().length();
  int tw=0;
  for (unsigned i=0;i<n;i++)
   {
     const MSString& aString=heading()[i];
     tw=MSUtil::max(tw,XTextWidth((XFontStruct *)headingFontStruct(),
				  (const char *)aString,aString.length()));
   }
  return tw;
}
