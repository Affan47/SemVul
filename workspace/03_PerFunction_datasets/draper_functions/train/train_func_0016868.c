word(unsigned wordNumber) const
{

  unsigned start=indexOfWord(wordNumber);
  unsigned end=0;
  if (start<length()) end=indexOfAnyOf(whiteSpace,start);
  if (end>start) return MSString(data()+start,end-start);
  else return MSString::null;
}
