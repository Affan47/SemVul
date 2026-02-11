Get_All_Partial_Lk(arbre *tree, edge *b_fcus, node *a, node *d)
{
  int i,j;
  double p1_lk1,p2_lk2;
  double ***p_lk,***p_lk_v1,***p_lk_v2;
  int catg,site;
  double ***Pij1,***Pij2;

  if(d->tax) return;
  else
    {
      int dir1,dir2;

      dir1=dir2=-1;
      For(i,3) if(d->v[i] != a) (dir1<0)?(dir1=i):(dir2=i);

      if(b_fcus->l < BL_MIN) b_fcus->l = BL_MIN;

      p_lk =
	(d == b_fcus->left)?
	(b_fcus->p_lk_left):
	(b_fcus->p_lk_rght);

      p_lk_v1 =
	(d == d->b[dir1]->left)?
	(d->b[dir1]->p_lk_rght):
	(d->b[dir1]->p_lk_left);

      p_lk_v2 =
	(d == d->b[dir2]->left)?
	(d->b[dir2]->p_lk_rght):
	(d->b[dir2]->p_lk_left);

      Pij1 = d->b[dir1]->Pij_rr;
      Pij2 = d->b[dir2]->Pij_rr;

      For(catg,tree->mod->n_catg)
	{
	  For(site,tree->n_pattern)
	    {
	      For(i,tree->mod->ns)
		{
		  p1_lk1 = p2_lk2 = .0;
		  For(j,tree->mod->ns)
		    {
		      p1_lk1 += (Pij1[catg][i][j] * p_lk_v1[site][catg][j]);
		      p2_lk2 += (Pij2[catg][i][j] * p_lk_v2[site][catg][j]);
		    }

		  p_lk[site][catg][i] = p1_lk1*p2_lk2;


		  if(p_lk[site][catg][i] < MDBL_MIN)
		    {
		      printf("\nWARNING : scaling is required at site %d\n",site);


		    }
		}
	    }
	}

    }
}
