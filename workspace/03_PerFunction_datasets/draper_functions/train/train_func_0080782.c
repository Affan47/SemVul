marshalType(unsigned char *&buffer, unsigned int &buflen) const
{

   if (!buffer)
   {
      buflen++;
      return true;
   }


   if (buflen < 1)
      return false;
   buflen--;


   *buffer++ = _type;
   return true;
}
