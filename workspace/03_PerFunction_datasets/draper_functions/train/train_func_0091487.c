verify_decrypted_buffer (EggBuffer *buffer)
{
        guchar digest[16];


	g_return_val_if_fail (gcry_md_get_algo_dlen (GCRY_MD_MD5) == sizeof (digest), 0);

	gcry_md_hash_buffer (GCRY_MD_MD5, (void*)digest,
			     (guchar*)buffer->buf + 16, buffer->len - 16);

	return memcmp (buffer->buf, digest, 16) == 0;
}
