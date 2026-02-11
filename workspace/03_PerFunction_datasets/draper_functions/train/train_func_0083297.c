get_subclass_covar(FILE * fd, struct SubSig *Sp, int nbands)
{
    int i, j;

    for (i = 0; i < nbands; i++)
	for (j = 0; j < nbands; j++)
	    fscanf(fd, "%lf", &Sp->R[i][j]);

    return 0;
}
