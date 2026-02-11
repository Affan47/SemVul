bs_Ccmp( s1, s2) UC *s1, *s2;
{
  REG int count=Itemcount, diff=0;
  while (count-- && !diff) diff = *s1++ - *s2++;
  return(diff);
}
