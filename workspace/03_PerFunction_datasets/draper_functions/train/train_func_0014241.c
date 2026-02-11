dnamove_copynode(node *fromnode, node *tonode)
{

  int i = 0;


  memcpy(tonode->base, fromnode->base, chars*sizeof(long));


  if (fromnode->numnuc != NULL)
    memcpy(tonode->numnuc, fromnode->numnuc, endsite*sizeof(nucarray));

  if (fromnode->numsteps != NULL)
    memcpy(tonode->numsteps, fromnode->numsteps, endsite*sizeof(long));

  tonode->numdesc = fromnode->numdesc;
  tonode->state   = fromnode->state;
  tonode->index   = fromnode->index;
  tonode->tip     = fromnode->tip;
  for (i=0;i<MAXNCH;i++)
    tonode->nayme[i] = fromnode->nayme[i];

}
