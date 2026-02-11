crypto_pk_copy_full(crypto_pk_t *env)
{
  RSA *new_key;
  int privatekey = 0;
  tor_assert(env);
  tor_assert(env->key);

  if (PRIVATE_KEY_OK(env)) {
    new_key = RSAPrivateKey_dup(env->key);
    privatekey = 1;
  } else {
    new_key = RSAPublicKey_dup(env->key);
  }
  if (!new_key) {
    log_err(LD_CRYPTO, "Unable to duplicate a %s key: openssl failed.",
            privatekey?"private":"public");
    crypto_log_errors(LOG_ERR,
                      privatekey ? "Duplicating a private key" :
                      "Duplicating a public key");
    tor_fragile_assert();
    return NULL;
  }

  return _crypto_new_pk_from_rsa(new_key);
}
