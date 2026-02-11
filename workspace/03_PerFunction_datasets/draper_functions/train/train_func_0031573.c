art_alphagamma_new (double gamma)
{
  int tablesize;
  ArtAlphaGamma *alphagamma;
  int i;
  int *table;
  art_u8 *invtable;
  double s, r_gamma;

  tablesize = ceil (gamma * 8);
  if (tablesize < 10)
    tablesize = 10;

  alphagamma = (ArtAlphaGamma *)art_alloc (sizeof(ArtAlphaGamma) +
					   ((1 << tablesize) - 1) *
					   sizeof(art_u8));
  alphagamma->gamma = gamma;
  alphagamma->invtable_size = tablesize;

  table = alphagamma->table;
  for (i = 0; i < 256; i++)
    table[i] = (int)floor (((1 << tablesize) - 1) *
			   pow (i * (1.0 / 255), gamma) + 0.5);

  invtable = alphagamma->invtable;
  s = 1.0 / ((1 << tablesize) - 1);
  r_gamma = 1.0 / gamma;
  for (i = 0; i < 1 << tablesize; i++)
    invtable[i] = (int)floor (255 * pow (i * s, r_gamma) + 0.5);

  return alphagamma;
}
