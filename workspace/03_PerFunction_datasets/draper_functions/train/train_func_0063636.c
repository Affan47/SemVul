addroot(double root, double *roots, int *rootnp)
{
    if (root >= 0 && root <= 1)
	roots[*rootnp] = root, (*rootnp)++;
}
