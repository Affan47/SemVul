main (int argc, char *argv[])
{
  int nail_bits, limb_bits, numb_bits;

  if (argc != 3)
    {
      fprintf (stderr, "Usage: gen-fac_ui limbbits nailbits\n");
      exit (1);
    }
  limb_bits = atoi (argv[1]);
  nail_bits = atoi (argv[2]);
  numb_bits = limb_bits - nail_bits;
  if (limb_bits < 0 || nail_bits < 0 || numb_bits < 0)
    {
      fprintf (stderr, "Invalid limb/nail bits %d,%d\n", limb_bits,
	       nail_bits);
      exit (1);
    }
  gen_consts (numb_bits, nail_bits, limb_bits);
  return 0;
}
