eet_data_get_short(const Eet_Dictionary *ed __UNUSED__,
                   const void           *src,
                   const void           *src_end,
                   void                 *dst)
{
   short *d;

   if (((char *)src + sizeof(short)) > (char *)src_end)
     return -1;

   memcpy(dst, src, sizeof(short));
   d = (short *)dst;
   CONV16(*d);
   return sizeof(short);
}
