getChar()
{
  if(hasUngotten)
    {
      hasUngotten=false;
      return ungotten;
    }
  return s[index++];
}
