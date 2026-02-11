decode_password (const char *ciphertext,
                 size_t      ciphertext_len,
                 const char *pin)
{
        gcry_cipher_hd_t hd = NULL;
        char *key = NULL;
        char *iv = NULL;
        char *password = NULL;

        key = make_key (pin);
        if (key == NULL)
                return NULL;

        if (gcry_cipher_open (&hd, GCRY_CIPHER_AES256,
                              GCRY_CIPHER_MODE_CBC, 0))
                goto out;

        iv = make_iv ();
        gcry_cipher_setiv (hd, iv, get_block_size ());
        gcry_cipher_setkey (hd, key, KEY_LENGTH);

        password = g_malloc (ciphertext_len + 1);
        if (password == NULL)
                goto out;

        if (gcry_cipher_decrypt (hd, password, ciphertext_len,
                                 ciphertext, ciphertext_len)) {
                g_free (password);
                password = NULL;
        } else {
                password[ciphertext_len] = 0;
        }

 out:
        g_free (key);
        g_free (iv);
        gcry_cipher_close (hd);
        return password;
}
