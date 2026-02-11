style(void) const
{
  unsigned long aStyle=_style!=0?_style:reportTable()->style();
  if ((aStyle&(MSLeft|MSRight|MSCenter))==0)
   {
     aStyle|=columnAlignment();
   }
  return aStyle;
}
