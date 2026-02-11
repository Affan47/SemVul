esl_wuss_nopseudo(char *ss1, char *ss2)
{
  while (*ss1 != '\0')
    {
      if (isalpha(*ss1)) *ss2 = '.';
      else *ss2 = *ss1;
      ss1++;
      ss2++;
    }
  *ss2 = '\0';
  return eslOK;
}
