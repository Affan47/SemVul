init_key_from_file(const char *fname, int generate, int severity)
{
  crypto_pk_t *prkey = NULL;

  if (!(prkey = crypto_pk_new())) {
    log(severity, LD_GENERAL,"Error constructing key");
    goto error;
  }

  switch (file_status(fname)) {
    case FN_DIR:
    case FN_ERROR:
      log(severity, LD_FS,"Can't read key from \"%s\"", fname);
      goto error;
    case FN_NOENT:
      if (generate) {
        if (!have_lockfile()) {
          if (try_locking(get_options(), 0)<0) {


            log(severity, LD_FS, "Another Tor process has locked \"%s\". Not "
                "writing any new keys.", fname);


            goto error;
          }
        }
        log_info(LD_GENERAL, "No key found in \"%s\"; generating fresh key.",
                 fname);
        if (crypto_pk_generate_key(prkey)) {
          log(severity, LD_GENERAL,"Error generating onion key");
          goto error;
        }
        if (crypto_pk_check_key(prkey) <= 0) {
          log(severity, LD_GENERAL,"Generated key seems invalid");
          goto error;
        }
        log_info(LD_GENERAL, "Generated key seems valid");
        if (crypto_pk_write_private_key_to_filename(prkey, fname)) {
          log(severity, LD_FS,
              "Couldn't write generated key to \"%s\".", fname);
          goto error;
        }
      } else {
        log_info(LD_GENERAL, "No key found in \"%s\"", fname);
      }
      return prkey;
    case FN_FILE:
      if (crypto_pk_read_private_key_from_filename(prkey, fname)) {
        log(severity, LD_GENERAL,"Error loading private key.");
        goto error;
      }
      return prkey;
    default:
      tor_assert(0);
  }

 error:
  if (prkey)
    crypto_pk_free(prkey);
  return NULL;
}
