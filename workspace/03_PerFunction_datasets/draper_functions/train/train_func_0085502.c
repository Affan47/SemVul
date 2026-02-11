StrMarkov0(char *s1, char *s2)
{
  int   len;
  int   pos;
  float p[26];


  len = strlen(s2);
  for (pos = 0; pos < len; pos++)
    if (! isalpha(s2[pos])) return 0;


  FSet(p, 26, 0.);
  for (pos = 0; pos < len; pos++)
    p[(int)(toupper(s2[pos]) - 'A')] += 1.0;
  FNorm(p, 26);


  for (pos = 0; pos < len; pos++)
    s1[pos] = FChoose(p, 26) + 'A';
  s1[pos] = '\0';

  return 1;
}
