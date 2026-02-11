gamgi_phys_projection_create (gamgi_enum model,
double **points, int *n_points, int **loops, int *n_loops)
{
int n;


n = 1;
if (model == GAMGI_PHYS_TRACE) n += GAMGI_MESA_PLANE_SLICES;
*points = (double *) malloc (3 * n * sizeof (double));
*n_points = n;


*loops = (int *) calloc (1, sizeof (int));
*n_loops = 1;
}
