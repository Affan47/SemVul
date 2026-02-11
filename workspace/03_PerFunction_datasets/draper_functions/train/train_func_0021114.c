sv_ReadBaseTransitionMatricesFlat_t(int t, FILE *f_in, TMarkovStateVariable *sv, TStateModel *model)
{
  int i, j;
  PRECISION sum;

  if (sv->n_state_variables > 0)
    {
      sv->t0=0;
      sv->t1=INT_MAX;
      for (i=0; i < sv->n_state_variables; i++)
	if (!sv_ReadBaseTransitionMatricesFlat_t(t,f_in,sv->state_variable[i],model))
	  {
	    sv->t1=-1;
	    return 0;
	  }
	else
	  {
	    if (sv->t0 < sv->state_variable[i]->t0) sv->t0=sv->state_variable[i]->t0;
	    if (sv->t1 > sv->state_variable[i]->t1) sv->t1=sv->state_variable[i]->t1;
	  }
      MatrixTensor(sv->baseQ,sv->QA);
      if (sv->nlags_encoded > 0) ConvertBaseTransitionMatrix(sv->Q,sv->baseQ,sv->nlags_encoded);
      return 1;
    }
  else
    {

      for (j=0; j < sv->nbasestates; j++)
	for (i=0; i < sv->nbasestates; i++)
	  if (fscanf(f_in," %lf ",&ElementM(sv->baseQ,i,j)) != 1)
	    {
	      sv->t1=-1;
	      dw_UserError("Unable to read transition matrix.");
	      return 0;
	    }


      for (j=sv->nbasestates-1; j >= 0; j--)
	{
	  for (sum=0.0, i=sv->nbasestates-1; i >= 0; i--)
	    if (ElementM(sv->baseQ,i,j) < 0.0)
	      {
		dw_UserError("Transition matrix can not have negative elements.");
		sv->t1=-1;
		return 0;
	      }
	    else
	      sum+=ElementM(sv->baseQ,i,j);
	  if (fabs(sum-1.0) > SQRT_MACHINE_EPSILON)
	    {
	      dw_UserError("Transition matrix columns must sum to one.");
	      sv->t1=-1;
	      return 0;
	    }
	  for (sum=1.0/sum, i=sv->nstates-1; i >= 0; i--)
	    ElementM(sv->baseQ,i,j)*=sum;
	}

      if (sv->nlags_encoded > 0) ConvertBaseTransitionMatrix(sv->Q,sv->baseQ,sv->nlags_encoded);


      if (!sv->routines || !sv->routines->Update_q_from_BaseTransitionMatrix || !sv->routines->Update_q_from_BaseTransitionMatrix(t,sv,model))
	{
	  dw_UserError("Unable to extract free parameters from transition matrix");
	  sv->t1=-1;
	  return 0;
	}
      else
	return 1;
    }
}
