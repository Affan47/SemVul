cipher_bench (int algo, int size)
{
  int ret;
  gnutls_cipher_hd_t ctx;
  void *_key, *_iv;
  gnutls_datum_t key, iv;
  struct timespec start, stop;
  double secs;
  double data_size = 0;
  double dspeed, ddata;
  int blocksize = gnutls_cipher_get_block_size (algo);
  int keysize = gnutls_cipher_get_key_size (algo);
  char metric[16];
#if defined(_WIN32)
  W32_ALARM_VARIABLES;
#endif

  _key = malloc (keysize);
  if (_key == NULL)
    return;
  memset (_key, 0xf0, keysize);

  _iv = malloc (blocksize);
  if (_iv == NULL)
    return;
  memset (_iv, 0xf0, blocksize);

  iv.data = _iv;
  iv.size = blocksize;

  key.data = _key;
  key.size = keysize;

  printf ("Checking %s (%dkb payload)... ", gnutls_cipher_get_name (algo),
          size);
  fflush (stdout);

  must_finish = 0;
#if !defined(_WIN32)
  alarm (5);
#else
  W32_ALARM_TRIGGER(5, goto leave);
#endif

  gettime (&start);

  ret = gnutls_cipher_init (&ctx, algo, &key, &iv);
  if (ret < 0)
    {
      fprintf (stderr, "error: %s\n", gnutls_strerror (ret));
      goto leave;
    }

  do
    {
      gnutls_cipher_encrypt (ctx, data, size * 1024);
      data_size += size * 1024;
    }
  while (must_finish == 0);

  gnutls_cipher_deinit (ctx);

  gettime (&stop);

  secs = (stop.tv_sec * 1000 + stop.tv_nsec / (1000 * 1000) -
          (start.tv_sec * 1000 + start.tv_nsec / (1000 * 1000)));
  secs /= 1000;

  value2human (data_size, secs, &ddata, &dspeed, metric);
  printf ("Encrypted %.2f %s in %.2f secs: ", ddata, metric, secs);
  printf ("%.2f %s/sec\n", dspeed, metric);

leave:
  free (_key);
  free (_iv);
#if defined(_WIN32)
  W32_ALARM_CLEANUP;
#endif
}
