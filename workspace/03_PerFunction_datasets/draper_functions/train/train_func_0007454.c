write_ugly_fasta(ESL_RANDOMNESS *r, FILE *fp, ESL_SQ *sq)
{
  char buf[61];
  int  pos;

  sq->roff = ftello(fp);
  fputc('>', fp);
  while (esl_rnd_Roll(r, 10) == 0) fputc(' ', fp);
  fprintf(fp, "%s", sq->name);
  while (esl_rnd_Roll(r, 10) == 0) fputc(' ', fp);
  if (sq->desc[0] != 0) fprintf(fp, " %s", sq->desc);
  fputc('\n', fp);

  sq->doff = ftello(fp);
  buf[60] = '\0';
  for (pos = 1; pos <= sq->n; pos+=60)
    {
      while (esl_rnd_Roll(r, 10) == 0) fputc(' ', fp);
      esl_abc_TextizeN(sq->abc, sq->dsq+pos, 60, buf);
      fputs(buf, fp);
      fputc('\n', fp);
    }
  while (esl_rnd_Roll(r, 10) == 0) fputc('\n', fp);
  sq->eoff = ftello(fp) - 1;
}
