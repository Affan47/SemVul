MSAAppendGR(MSA *msa, char *tag, int sqidx, char *value)
{
  int tagidx;
  int i;


  if (msa->gr_tag == NULL)
    {
      msa->gr_tag = MallocOrDie(sizeof(char *));
      msa->gr     = MallocOrDie(sizeof(char **));
      msa->gr[0]  = MallocOrDie(sizeof(char *) * msa->nseqalloc);
      for (i = 0; i < msa->nseqalloc; i++)
	msa->gr[0][i] = NULL;
      msa->gr_idx = GKIInit();
      tagidx      = GKIStoreKey(msa->gr_idx, tag);
      SQD_DASSERT1((tagidx == 0));
    }
  else
    {

      tagidx  = GKIKeyIndex(msa->gr_idx, tag);
      if (tagidx < 0) {
	tagidx = GKIStoreKey(msa->gr_idx, tag);


	SQD_DASSERT1((tagidx == msa->ngr));
	msa->gr_tag       = ReallocOrDie(msa->gr_tag, (msa->ngr+1) * sizeof(char *));
	msa->gr           = ReallocOrDie(msa->gr, (msa->ngr+1) * sizeof(char **));
	msa->gr[msa->ngr] = MallocOrDie(sizeof(char *) * msa->nseqalloc);
	for (i = 0; i < msa->nseqalloc; i++)
	  msa->gr[msa->ngr][i] = NULL;
      }
    }

  if (tagidx == msa->ngr) {
    msa->gr_tag[tagidx] = sre_strdup(tag, -1);
    msa->ngr++;
  }
  sre_strcat(&(msa->gr[tagidx][sqidx]), -1, value, -1);
  return;
}
