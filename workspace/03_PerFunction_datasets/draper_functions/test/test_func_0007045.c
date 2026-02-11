sinfo_transp_mx(Matrix a)
{
    register int nc=a->nc, nr=a->nr;
    register double *a0;
    register double *b0;
    register int i,j;
    Matrix b = sinfo_create_mx(nc,nr);

    if (b == (Matrix)NULL) return b ;
    for (i=0,b0=b->m;i<nc;i++)
        for (j=0,a0=a->m+i;j<nr;j++,a0+=nc,b0++)
            *b0 = *a0;
    return b;
}
