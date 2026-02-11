clarion_read_pic_desc (ClarionHandle *cl)
{
  int i;
  int numpics = cl->clm.clh->numpics;
  FILE *fp = cl->data;
  ClarionPicDesc *clp;

  if (numpics == 0)
    return 0;

  clp = (ClarionPicDesc *) malloc(numpics * sizeof(ClarionPicDesc));

  if (clp == NULL)
    return -1;

  for (i = 0; i < numpics; i++)
    {
      fread(&clp[i].piclen, 2, 1, fp);

      clp[i].picstr = (uint8_t *) malloc(clp[i].piclen + 1);

      fread(clp[i].picstr, 1, clp[i].piclen, fp);
      clp[i].picstr[clp[i].piclen] = '\0';
    }

  cl->clm.clp = clp;

  return 0;
}
