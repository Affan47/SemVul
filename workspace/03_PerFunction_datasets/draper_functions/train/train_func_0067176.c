toULong(
  const int pos, int &endpos, const int base) const
{
   char *edata=0;
   const unsigned long retval=strtoul(data+pos, &edata, base);
   if(edata)
   {
     endpos=(int)((size_t)edata-(size_t)data);
   }else
   {
     endpos=(-1);
   }
   return retval;
}
