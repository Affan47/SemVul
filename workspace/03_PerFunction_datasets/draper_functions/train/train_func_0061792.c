ValueToString(GLint value,
                          int valueTable[],
                          const char *stringTable[],
                          int tableSize)
{
  const char *result;
  bool found=false;
  int i=0;
  while(!found && i<tableSize)
    {
    found=valueTable[i]==value;
    ++i;
    }
  if(!found)
    {
    result=UnknownValue;
    }
  else
    {
    result=stringTable[i-1];
    }
  return result;
}
