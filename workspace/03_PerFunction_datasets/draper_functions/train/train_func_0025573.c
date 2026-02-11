kill(void)
{
  if (isProtected()==MSFalse&&text().length()>0)
   {
     int len=lineLength(cursorY())-cursorX();
     if (len>=0)
      {
	char *src=(char *)string();
	unsigned offset=line(cursorY())->start()+cursorX();
	if (len==0&&src[offset]==NewLineChar) len=1;
        else if (len>1)
         {
           unsigned index=len+offset-1;
           if (index<text().length())
            {
              if (src[index]==NewLineChar) len--;
            }
         }
	char *dest=new char[len+1];
	for (unsigned i=0;i<len;i++) dest[i]=src[i+offset];
	dest[len]='\0';
	yankBuffer()=dest;
	delete [] dest;
	deleteString(cursorPosition(),len);
      }
   }
}
