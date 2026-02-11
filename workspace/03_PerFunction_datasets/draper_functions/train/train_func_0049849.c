occurrencesOf(const MSStringTest &aTest,unsigned startPos) const
{
  unsigned count=0;
  while ((startPos=_pBuffer->indexOf(aTest,startPos))<_pBuffer->length()) count++,startPos++;
  return count;
}
