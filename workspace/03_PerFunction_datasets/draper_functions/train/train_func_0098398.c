crypto_seed_rng(int startup)
{
  int rand_poll_status = 0;


#ifdef _WIN32
  unsigned char buf[ADD_ENTROPY];
  static int provider_set = 0;
  static HCRYPTPROV provider;
#else
  char buf[ADD_ENTROPY];
  static const char *filenames[] = {
    "/dev/srandom", "/dev/urandom", "/dev/random", NULL
  };
  int fd, i;
  size_t n;
#endif


  if (startup || RAND_POLL_IS_SAFE) {
    rand_poll_status = RAND_poll();
    if (rand_poll_status == 0)
      log_warn(LD_CRYPTO, "RAND_poll() failed.");
  }

#ifdef _WIN32
  if (!provider_set) {
    if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT)) {
      if ((unsigned long)GetLastError() != (unsigned long)NTE_BAD_KEYSET) {
        log_warn(LD_CRYPTO, "Can't get CryptoAPI provider [1]");
        return rand_poll_status ? 0 : -1;
      }
    }
    provider_set = 1;
  }
  if (!CryptGenRandom(provider, sizeof(buf), buf)) {
    log_warn(LD_CRYPTO, "Can't get entropy from CryptoAPI.");
    return rand_poll_status ? 0 : -1;
  }
  RAND_seed(buf, sizeof(buf));
  memset(buf, 0, sizeof(buf));
  seed_weak_rng();
  return 0;
#else
  for (i = 0; filenames[i]; ++i) {
    fd = open(filenames[i], O_RDONLY, 0);
    if (fd<0) continue;
    log_info(LD_CRYPTO, "Seeding RNG from \"%s\"", filenames[i]);
    n = read_all(fd, buf, sizeof(buf), 0);
    close(fd);
    if (n != sizeof(buf)) {
      log_warn(LD_CRYPTO,
               "Error reading from entropy source (read only %lu bytes).",
               (unsigned long)n);
      return -1;
    }
    RAND_seed(buf, (int)sizeof(buf));
    memset(buf, 0, sizeof(buf));
    seed_weak_rng();
    return 0;
  }

  log_warn(LD_CRYPTO, "Cannot seed RNG -- no entropy source found.");
  return rand_poll_status ? 0 : -1;
#endif
}
