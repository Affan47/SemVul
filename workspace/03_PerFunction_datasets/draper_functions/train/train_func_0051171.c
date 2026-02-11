setNmiss(int varID, int levelID, int nvars, varinfo_t *varInfo, int nmiss)
{
  int vindex, lindex;
  int nlevs;

  for ( vindex = 0; vindex < nvars; vindex++ )
    if ( varInfo[vindex].varID == varID ) break;

  if ( vindex == nvars ) cdoAbort("Internal problem; varID not found!");

  nlevs = varInfo[vindex].nlevs;
  for ( lindex = 0; lindex < nlevs; lindex++ )
    if ( varInfo[vindex].levInfo[lindex].levelID == levelID ) break;

  if ( lindex == nlevs ) cdoAbort("Internal problem; levelID not found!");

  varInfo[vindex].levInfo[lindex].nmiss = nmiss;
}
