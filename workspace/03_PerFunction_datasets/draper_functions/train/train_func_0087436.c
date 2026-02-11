make_gamma_table (int range)
{
  int i;
  double factor =
    pow (256.0, 1.0 / (SANE_UNFIX (dc25_opt_gamma) / 10.0)) / range;
  unsigned char *gamma_table;
  if ((gamma_table = malloc (range * sizeof (unsigned char))) == NULL)
    {
      DBG (1, "make_gamma_table: can't allocate memory for gamma table\n");
      return NULL;
    }
  for (i = 0; i < range; i++)
    {
      int g =
	pow ((double) i * factor, (SANE_UNFIX (dc25_opt_gamma) / 10.0)) + 0.5;


      if (g > 255)
	g = 255;
      gamma_table[i] = g;
    }
  return gamma_table;
}
