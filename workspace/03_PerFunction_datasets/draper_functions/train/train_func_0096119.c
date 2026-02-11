possible(void)
#else
Boolean possible()
#endif
{
  AltElem *alt[MAXPARAMS+2];
  int i;

  fail = FALSE;
  alt[0] = findalt(header->vrbs, 0);

  if (alt[0] != 0 && alt[0]->checks != 0) {
    if (!trycheck(alt[0]->checks, FALSE)) return FALSE;
    if (fail) return FALSE;
  }


  alt[1] = findalt(locs[cur.loc-LOCMIN].vrbs, 0);
  if (alt[1] != 0 && alt[1]->checks != 0)
    if (!trycheck(alt[1]->checks, FALSE))
      return FALSE;

  for (i = 0; params[i].code != EOF; i++) {
    alt[i+2] = findalt(objs[params[i].code-OBJMIN].vrbs, i+1);

    if (alt[i+2] != 0 && alt[i+2]->checks != 0)
      if (!trycheck(alt[i+2]->checks, FALSE))
	return FALSE;
  }

  for (i = 0; i < 2 || params[i-2].code != EOF; i++)
    if (alt[i] != 0 && alt[i]->action != 0)
      break;
  if (i >= 2 && params[i-2].code == EOF)

    return FALSE;
  else
    return TRUE;
}
