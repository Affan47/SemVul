dSetRWork(int m, int panel_size, double *dworkptr,
	 double **dense, double **tempv)
{
    double zero = 0.0;

    int maxsuper = sp_ienv(3),
        rowblk   = sp_ienv(4);
    *dense = dworkptr;
    *tempv = *dense + panel_size*m;
    dfill (*dense, m * panel_size, zero);
    dfill (*tempv, NUM_TEMPV(m,panel_size,maxsuper,rowblk), zero);
}
