fpm_encrypt_field(	void* context,
			gchar* cipher_field,
			gchar* plaintext,
			gint len)
{
  gint i;
  gint num_blocks;
  byte* ciphertext;

  g_assert(blocksize>0);

  fpm_addnoise(plaintext, len);
  fpm_rotate(plaintext, len);


  num_blocks = len / blocksize;

  ciphertext = g_malloc(len);

  for(i=0; i<num_blocks; i++)
  {
    fpm_encrypt_block(context,
	 (ciphertext+i*blocksize), (byte *)(plaintext+i*blocksize) );
  }

  fpm_bin_to_hex(cipher_field, ciphertext, len);
  g_free(ciphertext);
}
