fpm_crypt_init(gchar* password) {
  gchar *prehash1 = "", *prehash2 = "";
  byte *hash_1, *hash_2;

  old_context = g_malloc(cipher->contextsize);
  new_context = g_malloc(cipher->contextsize);

  hash_1 = g_malloc(cipher->hash_len);
  hash_2 = g_malloc(cipher->hash_len);

  if(cipher_algo == AES256) {
    fpm_pkcs5_pbkdf2((guchar *)password, strlen(password), old_salt, cipher->salt_len, hash_1, cipher->hash_len, PBKDF2_ITERATIONS);
    fpm_pkcs5_pbkdf2((guchar *)password, strlen(password), new_salt, cipher->salt_len, hash_2, cipher->hash_len, PBKDF2_ITERATIONS);
  } else {
    prehash1 = g_strdup_printf("%s%s", old_salt, password);
    prehash2 = g_strdup_printf("%s%s", new_salt, password);

    md5(prehash1, hash_1);
    md5(prehash2, hash_2);
  }

  fpm_setkey(old_context, hash_1, cipher->hash_len);
  fpm_setkey(new_context, hash_2, cipher->hash_len);

  wipememory(hash_1, cipher->hash_len);
  wipememory(hash_2, cipher->hash_len);

  g_free(hash_1);
  g_free(hash_2);

  if (cipher_algo == BLOWFISH) {
    wipememory(prehash1, strlen(prehash1));
    wipememory(prehash2, strlen(prehash2));
    g_free(prehash1);
    g_free(prehash2);
  }
}
