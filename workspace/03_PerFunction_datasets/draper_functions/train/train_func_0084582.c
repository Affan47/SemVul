reallocchars(void)
{

  long i;
  node *p;

  if (usertree)
    for (i = 0; i < maxuser; i++) {
      free(fsteps[i]);
      fsteps[i] = (long *)Malloc(chars*sizeof(long));
    }

  for (i = 0; i < nonodes; i++) {
    reallocnode(treenode[i]);
    if (i >= spp) {
      p=treenode[i]->next;
      while (p != treenode[i])  {
        reallocnode(p);
        p = p->next;
      }
    }
  }

  free(weight);
  free(threshwt);
  free(temp->numsteps);
  free(temp->siteset);
  free(temp->seq);
  free(temp1->numsteps);
  free(temp1->siteset);
  free(temp1->seq);

  weight = (steptr)Malloc(chars*sizeof(long));
  threshwt = (steptr)Malloc(chars*sizeof(long));
  temp->numsteps = (steptr)Malloc(chars*sizeof(long));
  temp->siteset = (seqptr)Malloc(chars*sizeof(sitearray));
  temp->seq = (aas *)Malloc(chars*sizeof(aas));
  temp1->numsteps = (steptr)Malloc(chars*sizeof(long));
  temp1->siteset = (seqptr)Malloc(chars*sizeof(sitearray));
  temp1->seq = (aas *)Malloc(chars*sizeof(aas));
}
