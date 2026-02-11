eina_convert_atofp(const char *src, int length, Eina_F32p32 *fp)
{
   long long m;
   long e;

   if (!eina_convert_atod(src, length, &m, &e))
      return EINA_FALSE;

   if (!fp)
      return EINA_FALSE;

   e += 32;

   if (e > 0)
      *fp = m << e;
   else
      *fp = m >> -e;

   return EINA_TRUE;
}
