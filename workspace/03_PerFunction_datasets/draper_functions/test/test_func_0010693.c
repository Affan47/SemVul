eet_data_xattr_cipher_get(const char          *filename,
                          const char          *attribute,
                          Eet_Data_Descriptor *edd,
                          const char          *cipher_key)
{
   void *blob;
   void *ret;
   ssize_t size;

   blob = eina_xattr_get(filename, attribute, &size);
   if (!blob) return NULL;

   ret = eet_data_descriptor_decode_cipher(edd, blob, cipher_key, size);
   free(blob);

   return ret;
}
