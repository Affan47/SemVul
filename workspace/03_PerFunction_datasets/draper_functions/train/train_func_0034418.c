allocrest()
{
  long i;

  y       = (Char **)Malloc(spp*sizeof(Char *));
  for (i = 0; i < spp; i++)
    y[i] = (Char *)Malloc(sites*sizeof(Char));
  nayme        = (naym *)Malloc(maxsp * sizeof(naym));
  weight       = (steptr)Malloc(sites * sizeof(long));
  alias        = (steptr)Malloc(sites * sizeof(long));
  aliasweight  = (steptr)Malloc(sites * sizeof(long));
}
