MR_suppressK_client(Tree *tree,int tokensInChain[])
#else
int MR_suppressK_client(tree,tokensInChain)
  Tree      *tree;
  int       tokensInChain[];
#endif
{
  int       i;
  set       *save_fset;
  int       save_ConstrainSearch;
  set       incomplete;
  Tree      *t;

  suppressSucceeded=0;

  if (suppressSets == NULL) {
    suppressSets=(set *) calloc (CLL_k+1,sizeof(set));
    require (suppressSets != NULL,"MR_suppressK_client: suppressSets alloc");
  };

  for (suppressChainLength=1;
       tokensInChain[suppressChainLength+1] != 0;
       suppressChainLength++) {};

  require (suppressChainLength != 0,"MR_suppressK_client: chain empty");

  for (i=1 ; i <= suppressChainLength ; i++) {
    set_clr(suppressSets[i]);
    set_orel( (unsigned) tokensInChain[i],
                              &suppressSets[i]);
  };

  save_fset=fset;
  save_ConstrainSearch=ConstrainSearch;

  fset=suppressSets;

  MR_SuppressSearch=1;
  MR_AmbSourceSearch=1;
  MR_MaintainBackTrace=1;
  ConstrainSearch=1;

  maxk = suppressChainLength;

  incomplete=empty;
  t=NULL;


  MR_setConstrainPointer(&(fset[1]));

  MR_pointerStackReset(&MR_BackTraceStack);

  TRAV(suppressNode,maxk,&incomplete,t);

  Tfree(t);

  require (set_nil(incomplete),"MR_suppressK_client TRAV incomplete");
  require (MR_BackTraceStack.count == 0,
            "MR_suppressK_client: MR_BackTraceStack.count != 0");
  set_free(incomplete);

  ConstrainSearch=save_ConstrainSearch;
  fset=save_fset;

  MR_AmbSourceSearch=0;
  MR_MaintainBackTrace=0;
  MR_SuppressSearch=0;
  return suppressSucceeded;
}
