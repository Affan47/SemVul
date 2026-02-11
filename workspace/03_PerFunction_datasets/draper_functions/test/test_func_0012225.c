eet_data_put_int(Eet_Dictionary *ed __UNUSED__,
                 const void     *src,
                 int            *size_ret)
{
   int *s, *d;

   d = (int *)malloc(sizeof(int));
   if (!d)
     return NULL;

   s = (int *)src;
   *d = *s;
   CONV32(*d);
   *size_ret = sizeof(int);
   return d;
}
