ReadPhylip(MSAFILE *afp)
{
  MSA  *msa;
  char *s, *s1, *s2;
  char  name[11];
  int   nseq, alen;
  int   idx;
  int   slen;
  int   nblock;

  if (feof(afp->f)) return NULL;


  nseq = 0; alen = 0;
  while ((s = MSAFileGetLine(afp)) != NULL)
    {
      if ((s1 = sre_strtok(&s, WHITESPACE, NULL)) == NULL) continue;
      if ((s2 = sre_strtok(&s, WHITESPACE, NULL)) == NULL)
	Die("Failed to parse nseq/alen from first line of PHYLIP file %s\n", afp->fname);
      if (! IsInt(s1) || ! IsInt(s2))
	Die("nseq and/or alen not an integer in first line of PHYLIP file %s\n", afp->fname);
      nseq = atoi(s1);
      alen = atoi(s2);
      break;
    }

  msa = MSAAlloc(nseq, 0);
  idx    = 0;
  nblock = 0;
  while ((s = MSAFileGetLine(afp)) != NULL)
    {

      if (isspace(*s)) continue;

      if (nblock == 0) {
	strncpy(name, s, 10);
	name[10] = '\0';
	GKIStoreKey(msa->index, name);
	msa->sqname[idx] = sre_strdup(name, -1);
	s += 10;
      }

      if ((s1 = sre_strtok(&s, WHITESPACE, &slen)) == NULL)
	Die("Failed to parse sequence at line %d of PHYLIP file %s\n",
	    afp->linenumber, afp->fname);
      msa->sqlen[idx] = sre_strcat(&(msa->aseq[idx]), msa->sqlen[idx], s1, slen);

      idx++;
      if (idx == nseq) { idx = 0; nblock++; }
    }
  msa->nseq = nseq;
  MSAVerifyParse(msa);
  return msa;
}
