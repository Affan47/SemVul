clearsong(void)
{
  int c;

  for (c = 0; c < MAX_CHN; c++)
  {
    int d;
    for (d = 0; d < MAX_SONGS; d++)
    {
      memset(&songorder[d][c][0], 0, MAX_SONGLEN);
      if (!d)
      {
        songorder[d][c][0] = c;
        songorder[d][c][1] = LOOPSONG;
        songorder[d][c][2] = 0;
      }
      else
      {
        songorder[d][c][0] = LOOPSONG;
        songorder[d][c][1] = 0;
      }
    }
  }
  memset(songname, 0, sizeof songname);
  memset(authorname, 0, sizeof authorname);
  memset(copyrightname, 0, sizeof copyrightname);

  for (c = 0; c < MAX_PATT; c++)
  {
    int d;
    memset(&pattern[c][0], 0, MAX_PATTROWS*4);
    for (d = 0; d < MAX_PATTROWS; d++) pattern[c][d*4] = REST;
    for (d = MAX_PATTROWS; d <= MAX_PATTROWS; d++) pattern[c][d*4] = ENDPATT;
  }
  for (c = 0; c < MAX_INSTR; c++)
  {
    memset(&instr[c], 0, sizeof(INSTR));
  }
  memset(ltable, 0, sizeof ltable);
  memset(rtable, 0, sizeof rtable);
  countpatternlengths();
}
