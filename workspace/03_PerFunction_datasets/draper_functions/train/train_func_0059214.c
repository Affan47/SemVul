_cipher_bench (int algo)
{
  const char *algoname;
  int i;

  algoname = gcry_cipher_algo_name (algo);

  bench_print_header (14, algoname);

  for (i = 0; cipher_modes[i].mode; i++)
    cipher_bench_one (algo, &cipher_modes[i]);

  bench_print_footer (14);
}
