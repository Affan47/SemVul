set_password_hash(unsigned char *buf, int buf_size, char *passwd)
{
   unsigned char buffer[MESSAGE_BUF_SIZE];
   unsigned char md[MD5_HASH_SIZE];

   if (buf_size < MD5_HASH_SIZE) {
      return EXIT_FAILURE;
   }

   memset(buffer, 0, MESSAGE_BUF_SIZE);
   memcpy(buffer, buf, SALT_SIZE);
   strncpy((char *)(buffer+SALT_SIZE), passwd, MESSAGE_BUF_SIZE - SALT_SIZE - 1);
#ifdef HAVE_LIBGCRYPT
   gcry_md_hash_buffer(GCRY_MD_MD5, md, buffer, MESSAGE_BUF_SIZE);
#else
   MD5(buffer, MESSAGE_BUF_SIZE, md);
#endif


   memset(buffer, 0, MESSAGE_BUF_SIZE);

   if (memcmp(md, buf+SALT_SIZE, MD5_HASH_SIZE)) {
      return EXIT_FAILURE;
   }

#ifdef HAVE_LIBGCRYPT
   gcry_md_hash_buffer(GCRY_MD_MD5, md, passwd, strlen(passwd));
   memcpy(key, md, 16);
   memcpy(key+16, md, 8);
#else
   MD5((unsigned char *)passwd, strlen(passwd), md);
   memcpy(current_key1, md, 8);
   memcpy(current_key2, md+8, 8);
#ifdef HEADER_NEW_DES_H
   DES_set_key(&current_key1, &s1);
   DES_set_key(&current_key2, &s2);
#else
   des_set_key(&current_key1, s1);
   des_set_key(&current_key2, s2);
#endif
#endif

   return EXIT_SUCCESS;
}
