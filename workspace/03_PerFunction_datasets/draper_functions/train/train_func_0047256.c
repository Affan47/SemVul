revmemcpy (void *Dst, void *Src, const size_t len)
{
   size_t j;
   char *src = (char *) Src;
   char *dst = (char *) Dst;

   src = src + len - 1;
   for (j = 0; j < len; ++j) {
      *(dst++) = *(src--);
   }
   return Dst;
}
