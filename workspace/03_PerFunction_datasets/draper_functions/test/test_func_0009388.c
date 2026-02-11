crypto_pk_read_private_key_from_filename(crypto_pk_t *env,
                                         const char *keyfile)
{
  char *contents;
  int r;


  contents = read_file_to_str(keyfile, 0, NULL);
  if (!contents) {
    log_warn(LD_CRYPTO, "Error reading private key from \"%s\"", keyfile);
    return -1;
  }


  r = crypto_pk_read_private_key_from_string(env, contents, -1);
  memset(contents, 0, strlen(contents));
  tor_free(contents);
  if (r)
    return -1;


  if (crypto_pk_check_key(env) <= 0)
    return -1;

  return 0;
}
