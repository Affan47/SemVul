Update_SubTree_Partial_Lk(edge *b_fcus, node *a, node *d, arbre *tree)
{
  int i;

  Update_P_Lk(tree,b_fcus,a);
  if(d->tax) return;
  else For(i,3) if(d->v[i] != a)
    Update_SubTree_Partial_Lk(d->b[i],d,d->v[i],tree);
}
