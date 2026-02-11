Make_All_Edges_Lk(node *a, node *d, arbre *tree)
{
  int i;

  Make_Edge_Lk(a,d,tree);
  if(d->tax) return;
  else
    {
      For(i,3)
	{
	  if(d->v[i] != a)
	    Make_All_Edges_Lk(d,d->v[i],tree);
	}
    }
}
