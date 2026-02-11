symkey_decrypt_seskey( DEK *dek, byte *seskey, size_t slen )
{
  CIPHER_HANDLE hd;

  if(slen < 17 || slen > 33)
    {
      log_error ( _("weird size for an encrypted session key (%d)\n"),
		  (int)slen);
      return G10ERR_BAD_KEY;
    }

  hd = cipher_open( dek->algo, CIPHER_MODE_CFB, 1 );
  cipher_setkey( hd, dek->key, dek->keylen );
  cipher_setiv( hd, NULL, 0 );
  cipher_decrypt( hd, seskey, seskey, slen );
  cipher_close( hd );


  dek->keylen=slen-1;
  dek->algo=seskey[0];

  if(dek->keylen > DIM(dek->key))
    BUG ();

  memcpy(dek->key, seskey + 1, dek->keylen);


  return 0;
}
