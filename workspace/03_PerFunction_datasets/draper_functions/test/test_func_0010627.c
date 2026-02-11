p7_profile_Reuse(P7_PROFILE *gm)
{

  if (gm->name != NULL) { free(gm->name); gm->name = NULL; }
  if (gm->acc  != NULL) { free(gm->acc);  gm->acc  = NULL; }
  if (gm->desc != NULL) { free(gm->desc); gm->desc = NULL; }


  gm->rf[0]        = 0;
  gm->mm[0]        = 0;
  gm->cs[0]        = 0;
  gm->consensus[0] = 0;


  gm->mode = p7_NO_MODE;
  gm->L    = 0;
  gm->M    = 0;
  gm->nj   = 0.0f;

  gm->roff             = -1;
  gm->eoff             = -1;
  gm->offs[p7_MOFFSET] = -1;
  gm->offs[p7_FOFFSET] = -1;
  gm->offs[p7_POFFSET] = -1;

  return eslOK;
}
