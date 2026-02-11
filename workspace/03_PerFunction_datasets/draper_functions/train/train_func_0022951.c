c2b()
{
  if (length()!=0)
   {
     MSString     old(_pBuffer);
     MSStringBuffer *oldBuffer=_pBuffer;
     const char *pSource=oldBuffer->contents();
     unsigned    n     =oldBuffer->length();

     initBuffer(0,MSStringBuffer::checkMultiplication(n,8),0,0,0,0,'0');

     char *pDest=data();
     while (n--)
      {
	char c=*pSource++;
	unsigned int mask=1 << 8;
	while (mask >>= 1)
	*pDest++|=((c&mask)!=0);
      }
     oldBuffer->removeRef();
   }
  return *this;
}
