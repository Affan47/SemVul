verify_private_key(void)
{
  BIO *file;
  RSA *key;
  RSA *mkey;


  if (ServerInfo.rsa_private_key == NULL)
  {
    ilog(L_NOTICE, "rsa_private_key in serverinfo{} is not defined.");
    return -1;
  }


  if (ServerInfo.rsa_private_key_file == NULL)
  {
    ilog(L_NOTICE, "Internal error: rsa_private_key_file isn't defined.");
    return -1;
  }

  if (bio_spare_fd > -1)
    close(bio_spare_fd);

  file = BIO_new_file(ServerInfo.rsa_private_key_file, "r");


  if (file == NULL)
  {
    bio_spare_fd = save_spare_fd("SSL private key validation");
    ilog(L_NOTICE, "Failed to open private key file - can't validate it");
    return -1;
  }

  key = PEM_read_bio_RSAPrivateKey(file, NULL, 0, NULL);

  if (key == NULL)
  {
    ilog(L_NOTICE, "PEM_read_bio_RSAPrivateKey() failed; possibly not RSA?");
    report_crypto_errors();
    return -1;
  }

  BIO_set_close(file, BIO_CLOSE);
  BIO_free(file);
  bio_spare_fd = save_spare_fd("SSL private key validation");

  mkey = ServerInfo.rsa_private_key;


  if (mkey->pad != key->pad)
    ilog(L_CRIT, "Private key corrupted: pad %i != pad %i",
                 mkey->pad, key->pad);

  if (mkey->version != key->version)
    ilog(L_CRIT, "Private key corrupted: version %li != version %li",
                 mkey->version, key->version);

  if (BN_cmp(mkey->n, key->n))
    ilog(L_CRIT, "Private key corrupted: n differs");
  if (BN_cmp(mkey->e, key->e))
    ilog(L_CRIT, "Private key corrupted: e differs");
  if (BN_cmp(mkey->d, key->d))
    ilog(L_CRIT, "Private key corrupted: d differs");
  if (BN_cmp(mkey->p, key->p))
    ilog(L_CRIT, "Private key corrupted: p differs");
  if (BN_cmp(mkey->q, key->q))
    ilog(L_CRIT, "Private key corrupted: q differs");
  if (BN_cmp(mkey->dmp1, key->dmp1))
    ilog(L_CRIT, "Private key corrupted: dmp1 differs");
  if (BN_cmp(mkey->dmq1, key->dmq1))
    ilog(L_CRIT, "Private key corrupted: dmq1 differs");
  if (BN_cmp(mkey->iqmp, key->iqmp))
    ilog(L_CRIT, "Private key corrupted: iqmp differs");

  RSA_free(key);
  return 0;
}
