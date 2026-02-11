Get_Bip(node *a, node *d, arbre *tree)
{
  if(d->tax)
    {
      d->bip_node[0][0] = d;
      d->bip_size[0]    = 1;
      return;
    }
  else
    {
      int i,j,k;
      int d_a;


      d_a = -1;

      For(i,3)
	{
	  if(d->v[i] != a)
	    Get_Bip(d,d->v[i],tree);
	  else d_a = i;
	}

      d->bip_size[d_a] = 0;
      For(i,3)
	if(d->v[i] !=a )
	  {
	    For(j,3)
	      {
		if(d->v[i]->v[j] == d)
		  {
		    For(k,d->v[i]->bip_size[j])
		      {
			d->bip_node[d_a][d->bip_size[d_a]] = d->v[i]->bip_node[j][k];
			strcpy(d->bip_name[d_a][d->bip_size[d_a]],d->v[i]->bip_node[j][k]->name);
			d->bip_size[d_a]++;
		      }
		    break;
		  }
	      }
	  }

      qsort(d->bip_name[d_a],d->bip_size[d_a],sizeof(char *),Sort_String);

      For(i,3)
	if(a->v[i] == d)
	  {
	    a->bip_size[i] = 0;
	    For(j,tree->n_otu)
	      {
		For(k,d->bip_size[d_a])
		  {
		    if(d->bip_node[d_a][k] == tree->noeud[j])
		      break;
		  }

		if(k == d->bip_size[d_a])
		  {
		    a->bip_node[i][a->bip_size[i]] = tree->noeud[j];
		    strcpy(a->bip_name[i][a->bip_size[i]],tree->noeud[j]->name);
		    a->bip_size[i]++;
		  }
	      }

	    qsort(a->bip_name[i],a->bip_size[i],sizeof(char *),Sort_String);

	    if(a->bip_size[i] != tree->n_otu - d->bip_size[d_a])
	      {
		printf("%d %d \n",a->bip_size[i],tree->n_otu - d->bip_size[d_a]);
		Exit("\n. Problem in counting bipartitions \n");
	      }
	    break;
	  }
    }
}
