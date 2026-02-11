Reg_Interpolate(InstanceVars I, POINT_TYPE *pt, VECTOR_TYPE *vec)
{
    Reg_InstanceVars iI    = (Reg_InstanceVars)I;
    Reg_VectorGrp    iP    = (Reg_VectorGrp)iI->i.currentVectorGrp;
    Reg_VectorPart   ip    = (Reg_VectorPart)iP->P.p[iI->cp];
    int		     nDim  = iP->P.nDim;
    int		     nVrts = 1 << nDim;
    int		     *ind  = iI->indices;
    int		     *strd = ip->strides;
    int		     *bump = ip->bumps;
    double	     *w    = iI->weights;
    int		     base;
    float	     *vector;
    int		     i, j;

    if (ip->constantData)
    {
	for (i = 0; i < nDim; i++)
	    vec[i] = (VECTOR_TYPE)ip->vectors[i];
	return OK;
    }

    if (ip->p.dependency == DEP_ON_POSITIONS)
    {
	base = 0;
	for (i = 0; i < nDim; i++)
	    base += *ind++ * *strd++;

	vec[0] = vec[1] = vec[2] = 0.0;
	for (i = 0; i < nVrts; i++, bump++, w++)
	{
	    vector = ip->vectors + nDim*(base + *bump);
	    for (j = 0; j < nDim; j++)
		vec[j] += *w * *vector++;
	}
    }
    else
    {
	base = 0;
	for (i = 0; i < nDim; i++)
	    base += *ind++ * *strd++;

	vector = ip->vectors + nDim*base;
	for (j = 0; j < nDim; j++)
	    vec[j] = *vector++;
    }

    return OK;
}
