dcheck_tempv(int n, double *tempv)
{
    int i;

    for (i = 0; i < n; i++) {
	if (tempv[i] != 0.0)
	{
	    fprintf(stderr,"tempv[%d] = %f\n", i,tempv[i]);
	    ABORT("dcheck_tempv");
	}
    }
}
