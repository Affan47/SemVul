CMSimpleProbify(CM_t *cm)
{
  int v,x;

  for (v = 0; v < cm->M; v++)
    {


      if (cm->sttype[v] != B_st && cm->sttype[v] != E_st)
	{
	  for (x = 0; x < cm->cnum[v]; x++) cm->t[v][x] += 1.0;
	  esl_vec_FNorm(cm->t[v], cm->cnum[v]);
	}


      if (cm->sttype[v] == MP_st)
	{
	  for (x = 0; x < cm->abc->K*cm->abc->K; x++) cm->e[v][x] += 1.0;
	  esl_vec_FNorm(cm->e[v], cm->abc->K*cm->abc->K);
	}
      else if (cm->sttype[v] == ML_st || cm->sttype[v] == MR_st ||
	       cm->sttype[v] == IL_st || cm->sttype[v] == IR_st)
	{
	  for (x = 0; x < cm->abc->K; x++) cm->e[v][x] += 1.0;
	  esl_vec_FNorm(cm->e[v], cm->abc->K);
	}
    }
}
