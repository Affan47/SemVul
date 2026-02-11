eet_data_image_read_cipher(Eet_File     *ef,
                           const char   *name,
                           const char   *cipher_key,
                           unsigned int *w,
                           unsigned int *h,
                           int          *alpha,
                           int          *comp,
                           int          *quality,
                           int          *lossy)
{
   unsigned int *d = NULL;
   void *data = NULL;
   int free_data = 0;
   int size;

   if (!cipher_key)
     data = (void *)eet_read_direct(ef, name, &size);

   if (!data)
     {
        data = eet_read_cipher(ef, name, &size, cipher_key);
        free_data = 1;
        if (!data)
          return NULL;
     }

   d = eet_data_image_decode(data, size, w, h, alpha, comp, quality, lossy);

   if (free_data)
     free(data);

   return d;
}
