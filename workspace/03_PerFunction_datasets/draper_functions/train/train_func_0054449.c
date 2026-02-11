buildtree()
{
  long i, j, nextnode;
  node *p;
  char* treestr;

  changed = false;
  newtree = false;
  switch (how) {

  case arb:
    arbitree();
    break;

  case use:
    names = (boolean *)Malloc(spp*sizeof(boolean));
    firsttree = true;
    nodep = NULL;
    nextnode = 0;
    haslengths = 0;
    zeros = (long *)Malloc(chars*sizeof(long));
    for (i = 0; i < chars; i++)
      zeros[i] = 0;
    treestr = ajStrGetuniquePtr(&phylotrees[0]->Tree);
    treeread(&treestr, &root, treenode, &goteof, &firsttree,
                nodep, &nextnode, &haslengths,
                &grbg, initdolmovenode,false,nonodes);
    for (i = spp; i < (nonodes); i++) {
      p = treenode[i];
      for (j = 1; j <= 3; j++) {
        p->stateone = (bitptr)Malloc(words*sizeof(long));
        p->statezero = (bitptr)Malloc(words*sizeof(long));
        p = p->next;
      }
    }


    for (i = 0; i < (spp); i++)
      in_tree[i] = names[i];
    free(names);
    FClose(intree);
    break;

  case spec:
    yourtree();
    break;
  }
  outgrno = root->next->back->index;
  if (in_tree[outgrno - 1])
    reroot(treenode[outgrno - 1]);
}
