skip(size_t len)
{
   const char *chars = "\xc0\xde\xba\xbe";

   if (!this->ok)
      return false;

   for (size_t n = 0; n < len; n++)
   {
      if (!this->write<int8_t>(chars[n & 3]))
	 break;
   }

   return this->ok;
}
