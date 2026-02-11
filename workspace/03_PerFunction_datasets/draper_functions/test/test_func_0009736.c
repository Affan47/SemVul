get_pat_cases(UCS *realpat, UCS *searchpat)
{
  int i, searchpatlen, curoff;

  curoff = curwp->w_doto;
  searchpatlen = ucs4_strlen(searchpat);

  for (i = 0; i < searchpatlen; i++)
    realpat[i] = lgetc(curwp->w_dotp, curoff++).c;

  realpat[searchpatlen] = '\0';
}
