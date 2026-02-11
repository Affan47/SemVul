printClose(void)
{
  MSBoolean status=MSTrue;
  if (outputMode()==PPM)
   {
     printPixmap();
     pout.close();
   }
  else
   {
     printClear();
     status=MSPostScript::printClose();
   }
  return status;
}
