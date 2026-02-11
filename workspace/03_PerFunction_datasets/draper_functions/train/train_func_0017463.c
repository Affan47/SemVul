main (int argc, char **argv)
{
  int  limb_bits, nail_bits;

  mpz_init (big_base);
  mpz_init (big_base_inverted);
  mpz_init (t);

  if (argc != 4)
    {
      fprintf (stderr, "Usage: gen-bases <header|table> <limbbits> <nailbits>\n");
      exit (1);
    }

  limb_bits = atoi (argv[2]);
  nail_bits = atoi (argv[3]);

  if (limb_bits <= 0
      || nail_bits < 0
      || nail_bits >= limb_bits)
    {
      fprintf (stderr, "Invalid limb/nail bits: %d %d\n",
               limb_bits, nail_bits);
      exit (1);
    }

  if (strcmp (argv[1], "header") == 0)
    header (limb_bits, nail_bits);
  else if (strcmp (argv[1], "table") == 0)
    table (limb_bits, nail_bits);
  else
    {
      fprintf (stderr, "Invalid header/table choice: %s\n", argv[1]);
      exit (1);
    }

  return 0;
}
