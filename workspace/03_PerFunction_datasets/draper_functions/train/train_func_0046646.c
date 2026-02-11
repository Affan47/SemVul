allocrest()
{
  long i;

  y = (Char **)Malloc(spp*sizeof(Char *));
  for (i = 0; i < spp; i++)
    y[i] = (Char *)Malloc(sites*sizeof(Char));
  nayme = (naym *)Malloc(spp*sizeof(naym));
  enterorder = (long *)Malloc(spp*sizeof(long));
  weight = (steptr)Malloc((sites+1)*sizeof(long));
  alias = (steptr)Malloc((sites+1)*sizeof(long));
  aliasweight = (steptr)Malloc((sites+1)*sizeof(long));
}
