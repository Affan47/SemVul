PMat_Empirical(double l, model *mod, double ***Pij)
{
  int n = mod->ns;
  int i, j, k;
  double *U,*V,*R;
  double *expt  = (double*)calloc(n,sizeof(double));
  double *uexpt = (double*)calloc(n*n,sizeof(double));

  U = mod->mat_Vr;
  V = mod->mat_Vi;
  R = mod->vct_eDmr;

  For (i,n) For (k,n)
    (*Pij)[i][k] = .0;


  For (k,n)  expt[k] = pow(R[k], l);


  For (i,n) For (k,n)
    uexpt[i*n+k] = U[i*n+k] * expt[k];
  For (i,n)
    {
      For (j,n)
	{
	  For(k,n)
	    {
	      (*Pij)[i][j] += uexpt[i*n+k] * V[k*n+j];
	    }
	  if((*Pij)[i][j] < MDBL_MIN)
	    (*Pij)[i][j] = MDBL_MIN;
	}
    }

  free(expt);
  free(uexpt);
}
