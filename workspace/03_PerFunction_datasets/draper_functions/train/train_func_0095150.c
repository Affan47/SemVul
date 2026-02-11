gt_symbolstring2fasta(FILE *fpout,
                        const char *desc,
                        const GtAlphabet *alpha,
                        const GtUchar *w,
                        unsigned long wlen,
                        unsigned long width)
{
  unsigned long i, j;
  GtUchar currentchar;

  gt_assert(width > 0);
  if (desc == NULL)
  {
    fprintf(fpout,">\n");
  } else
  {
    fprintf(fpout,">%s\n",desc);
  }
  for (i = 0, j = 0; ; i++)
  {
    currentchar = w[i];
    if (currentchar == (GtUchar) SEPARATOR)
    {
      fprintf(fpout,"\n>\n");
      j = 0;
    } else
    {
      gt_alphabet_echo_pretty_symbol(alpha,fpout,currentchar);
    }
    if (i == wlen - 1)
    {
      fprintf(fpout,"\n");
      break;
    }
    if (currentchar != (GtUchar) SEPARATOR)
    {
      j++;
      if (j >= width)
      {
        fprintf(fpout,"\n");
        j = 0;
      }
    }
  }
}
