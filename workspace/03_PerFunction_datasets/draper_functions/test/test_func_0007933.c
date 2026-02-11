seedPRNG(const char *randFile)
{
#ifdef _WIN32
  RAND_screen();
#endif
  if (randFile)
  {
    if (RAND_egd(randFile) <= 0)
    {
      RAND_load_file(randFile ,-1);
    }
  }
  if (RAND_status()) canWriteRandseed = OFTrue;
  else
  {

    DCMTLS_WARN("PRNG for TLS not seeded with sufficient random data.");
  }
}
