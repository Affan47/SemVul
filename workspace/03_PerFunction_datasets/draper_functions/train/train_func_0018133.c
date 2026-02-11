kill(void)
{
  if(masking() == MSFalse)
   {
     const char *pString=string();
     yankBuffer()=(pString+cursorPosition());
     deleteString(cursorPosition(),length()-cursorPosition());
   }
}
