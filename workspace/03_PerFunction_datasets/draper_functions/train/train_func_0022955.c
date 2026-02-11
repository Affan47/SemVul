test_start (void)
{
  char *environment_seed;
  unsigned long seed;

  if (rands_initialized)
    {
      fprintf (stderr,
               "Put test_start at the beginning of your test function.\n");
      exit (1);
    }

  gmp_randinit_default (rands);
  rands_initialized = 1;

  environment_seed = getenv ("GMP_CHECK_RANDOMIZE");
  if (environment_seed == NULL)
      gmp_randseed_ui (rands, 0xfac11e);
  else
    {
      seed = (unsigned long int) atoi (environment_seed);
      if (seed == 0 || seed == 1)
        {
#if defined HAVE_GETTIMEOFDAY
          struct timeval  tv;
          gettimeofday (&tv, NULL);
          seed = (unsigned long int) (tv.tv_sec + tv.tv_usec);
#else
          time_t  tv;
          time (&tv);
          seed = (unsigned long int) tv;
#endif
          gmp_randseed_ui (rands, seed);
          printf ("Seed GMP_CHECK_RANDOMIZE=%lu "
                  "(include this in bug reports)\n", seed);
        }
      else
        {
          printf ("Re-seeding with GMP_CHECK_RANDOMIZE=%lu\n", seed);
          gmp_randseed_ui (rands, seed);
        }
    }
}
