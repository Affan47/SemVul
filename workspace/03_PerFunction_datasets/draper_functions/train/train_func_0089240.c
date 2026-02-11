removelowercaseproteinchars(GtUchar *domainbuf,
                                                const GtAlphabet *alpha)
{
  unsigned int i, j = 0;

  for (i=0; i< alpha->domainsize - alpha->mappedwildcards; i++)
  {
    if (isalnum((int) alpha->mapdomain[i]) &&
        isupper((int) alpha->mapdomain[i]))
    {
      domainbuf[j++] = alpha->mapdomain[i];
    }
  }
  return j;
}
