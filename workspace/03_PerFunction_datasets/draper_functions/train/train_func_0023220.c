embIepCalcK(double *K, double **pK)
{
    ajint i;

    for(i=0;i<EMBIEPSIZE;++i)
	if(!pK[i][0])
	    K[i] = 0.0;
	else
	    K[i] = embIepPkToK(pK[i][0]);

    return;
}
