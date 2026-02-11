cptInit(CPT *cpt)
{
  int k;

  cpt->ncolors = 0;
  for ( k = 0; k < 3; k++ )
    {
      cpt->bfn[k].rgb[0] = 0;
      cpt->bfn[k].rgb[1] = 0;
      cpt->bfn[k].rgb[2] = 0;
      cpt->bfn[k].skip = TRUE;
    }
}
