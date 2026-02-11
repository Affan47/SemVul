_gcry_rngfips_run_external_test (void *context, char *buffer, size_t buflen)
{
  rng_context_t test_ctx = context;

  if (!test_ctx || !buffer || buflen != 16)
    return GPG_ERR_INV_ARG;

  lock_rng ();
  get_random (buffer, buflen, test_ctx);
  unlock_rng ();
  return 0;
}
