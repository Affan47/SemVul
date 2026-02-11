dump (char *name, mpz_t in1, mpz_t in2, mpz_t in3)
{
  printf ("failure in %s (", name);
  mpz_out_str (stdout, -16, in1);
  if (in2 != NULL)
    {
      printf (" ");
      mpz_out_str (stdout, -16, in2);
    }
  if (in3 != NULL)
    {
      printf (" ");
      mpz_out_str (stdout, -16, in3);
    }
  printf (")\n");
}
