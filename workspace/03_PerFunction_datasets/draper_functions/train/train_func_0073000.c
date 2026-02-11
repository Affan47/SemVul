hmmlogo_maxHeight (P7_BG *bg)
{
  float min_p = 1;
  int i;
  for (i=0; i<bg->abc->K; i++)
    min_p = ESL_MIN(min_p,bg->f[i]);

  return eslCONST_LOG2R * log(1.0/min_p);
}
