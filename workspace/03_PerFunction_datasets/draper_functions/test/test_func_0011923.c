Set_Model_Parameters(arbre *tree)
{
  double sum;
  int i;


  DiscreteGamma (tree->mod->r_proba, tree->mod->rr, tree->mod->alpha,
		 tree->mod->alpha,tree->mod->n_catg,0);


  if((tree->mod->whichmodel < 10) && (tree->mod->s_opt->opt_bfreq))
    {
      sum = .0;
      For(i,4) sum += tree->mod->pi[i];
      For(i,4)
	{
	  tree->mod->pi[i] /= sum;

	}
    }


  if(tree->mod->whichmodel >= 7)
    {
        For(i,6)
            {
                tree->mod->rr_param_values[i] /= tree->mod->rr_param_values[5];
            }
    }

  if(tree->mod->update_eigen)
    {
      if(tree->mod->datatype == NT)
	{
	  if(tree->mod->whichmodel < 20) Update_Qmat_GTR(tree->mod);
	}
    }

}
