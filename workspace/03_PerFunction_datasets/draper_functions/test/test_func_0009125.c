lowerCase()
{
  MSStringBuffer *result=this;
  unsigned pos=indexOfAnyOf(caps,26,0);
  if (pos<length())
   {
     if (useCount()>1) result=newBuffer(contents(),length());
     else addRef();
     char *p=result->contents();
     while (pos<length())
      {
	if (charType(pos)==MSStringEnum::SBCS) p[pos]+='a'-'A';
	pos=indexOfAnyOf(caps,26,pos+1);
      }
   }
  else addRef();
  return result;
}
