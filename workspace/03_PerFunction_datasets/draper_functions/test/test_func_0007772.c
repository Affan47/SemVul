Best_Pair(matrix *mat, int *x, int *y,double *score)
{
  int i,j;
  double Qij,Qmin,Qmin2;
  double **t_Qij;

  t_Qij = (double **)mCalloc(mat->n_otu,sizeof(double *));
  For(i,mat->n_otu)
    t_Qij[i] = (double *)mCalloc(mat->n_otu,sizeof(double));

  Qmin = 1.e+10;
  Qij = Qmin;

  For(i,mat->n_otu)
    {
      if(mat->on_off[i])
	{
	  for(j=0;j<i;j++)
	    {
	      if(mat->on_off[j])
		{
		  Qij = Q_Agglo(mat,i,j);
		  t_Qij[i][j] = Qij;

		  if(Qij < Qmin)
		    {
		      *x = i;
		      *y = j;
		      Qmin = Qij;
		    }
		}
	    }
	}
    }

  Qmin2 = 1e+10;

  For(i,mat->n_otu)
    {
      if((i != *y) && (i != *x) && (t_Qij[*x][i] < Qmin2)) Qmin2 = t_Qij[*x][i];
    }

  For(i,mat->n_otu)
    {
      if((i != *y) && (i != *x) && (t_Qij[i][*y] < Qmin2)) Qmin2 = t_Qij[i][*y];
    }

  *score = fabs(Qmin2 - Qmin)/fabs(Qmin);

  For(i,mat->n_otu) free(t_Qij[i]);
  free(t_Qij);
}
