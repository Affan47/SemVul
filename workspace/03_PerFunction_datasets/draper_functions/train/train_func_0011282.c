_gcry_set_random_seed_file (const char *name)
{
  if (fips_mode ())
    ;
  else if (rng_types.standard)
    _gcry_rngcsprng_set_seed_file (name);
  else if (rng_types.fips)
    ;
  else if (rng_types.system)
    ;
  else
    _gcry_rngcsprng_set_seed_file (name);
}
