EmptyQueues(MatroskaFile *mf) {
  unsigned	    i;

  for (i=0;i<mf->nTracks;++i)
    ClearQueue(mf,&mf->Queues[i]);
}
