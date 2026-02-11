static_create_all (gamgi_cell *cell, int *index,
double *transformation, double *orientation)
{
double u[3], v[3], translate[3];
int n, h, k, l;
gamgi_enum vectors;

if (cell->model == GAMGI_PHYS_CONVENTIONAL)
  vectors = GAMGI_PHYS_CONVENTIONAL;
else
  vectors = GAMGI_PHYS_PRIMITIVE;

for (n = 0; n < cell->n_nodes; n++)
  {
  h = index[3*n + 0];
  k = index[3*n + 1];
  l = index[3*n + 2];


  gamgi_math_matrix_vector (transformation, cell->points + 3*n, u);

  gamgi_math_vector_sub (u, cell->center, v);
  gamgi_math_matrix_vector (orientation, v, u);
  gamgi_math_vector_add (u, cell->center, v);


  if (n == 0)
    gamgi_math_vector_sub (cell->origin, v, translate);


  if (gamgi_phys_direction_zero (index + 3*n) == FALSE)
    {
    gamgi_math_vector_add (v, translate, u);
    static_create (cell, vectors, h, k, l, u);
    }
  }
}
