crypto_pk_num_bits(crypto_pk_t *env)
{
  tor_assert(env);
  tor_assert(env->key);
  tor_assert(env->key->n);

  return BN_num_bits(env->key->n);
}
