treerepcount(YYSTYPE v, int* rc)
{
  if(!v) return;
  if(!(v->nodetypename)&&v->replnum&&!(v->cxneeded)) rc[v->replnum]++;
  treerepcount(v->n1, rc);
  treerepcount(v->n2, rc);
}
