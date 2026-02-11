composition(char *s, int L, int *mono, int **di)
{
  int i, x, y;

  for (x = 0; x < 26; x++) {
    mono[x] = 0;
    for (y = 0; y < 26; y++)
      di[x][y] = 0;
  }

  for (i = 0; s[i] != '\0'; i++) {
    if (!isalpha(s[i])) esl_fatal("bad residue %d", i);
    y = toupper(s[i]) - 'A';
    mono[y]++;
    if (i > 0) {
      x = toupper(s[i-1] - 'A');
      di[x][y]++;
    }
  }
  if (i != L) esl_fatal("sequence length didn't match expected %d", L);
  return eslOK;
}
