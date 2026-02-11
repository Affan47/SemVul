mkv_GetLowestQTimecode(MatroskaFile *mf) {
  unsigned  n,seen;
  ulonglong t;


  for (n=seen=0,t=0;n<mf->nTracks;++n)
    if (mf->Queues[n].head && (!seen || t > mf->Queues[n].head->Start))
      t = mf->Queues[n].head->Start, seen=1;

  return seen ? t : (ulonglong)LL(-1);
}
