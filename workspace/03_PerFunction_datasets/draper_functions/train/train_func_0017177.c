applyall(const char *alpha,
                              unsigned long textlen,void *info,
                              unsigned long (*apply)(const GtUchar *,
                                                     unsigned long,
                                                     void *))
{
  unsigned long i, *w, z = textlen-1,
                testcases = 0,
                asize = (unsigned long) strlen(alpha);
  GtUchar *text;
  bool stop = false;

  w = gt_malloc(sizeof *w * (textlen+1));
  text = gt_malloc(sizeof *text * (textlen+1));
  for (i=0; i<=textlen; i++)
  {
    w[i] = 0;
  }
  text[textlen] = (GtUchar) '\0';
  while (!stop)
  {
    for (i = 0; i<textlen; i++)
    {
      text[i] = (GtUchar) alpha[w[i]];
    }
    testcases += apply(text,textlen,info);
    while (true)
    {
      w[z]++;
      if (w[z] == asize)
      {
        w[z] = 0;
        if (z == 0)
        {
          stop = true;
          break;
        }
        z--;
      } else
      {
        z = textlen-1;
         break;
      }
    }
  }
  gt_free(w);
  gt_free(text);
  return testcases;
}
