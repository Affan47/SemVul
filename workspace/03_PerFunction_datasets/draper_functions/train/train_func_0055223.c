eet_data_text_undump_cipher(const char *text,
                            const char *cipher_key,
                            int         textlen,
                            int        *size_ret)
{
   void *ret = NULL;

   ret = _eet_data_dump_parse(NULL, size_ret, text, textlen);
   if (ret && cipher_key)
     {
        void *ciphered = NULL;
        unsigned int ciphered_len;

        if (eet_cipher(ret, *size_ret, cipher_key,
                       strlen(cipher_key), &ciphered, &ciphered_len))
          {
             if (ciphered)
               free(ciphered);

             size_ret = 0;
             free(ret);
             return NULL;
          }

        free(ret);
        *size_ret = ciphered_len;
        ret = ciphered;
     }

   return ret;
}
