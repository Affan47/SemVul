gamgi_phys_cell_parallelepiped_create (gamgi_cell *cell, int n_nodes)
{
double *points;
double base[9], inverse[9];
double v1[3], v2[3], v3[3];
double position[3];
int range[6];
int i, j, k;
int offset;


gamgi_math_cell_vectors (cell->v1, cell->v2,  cell->v3,
cell->v12, cell->v13,  cell->v23, v1, v2, v3);

gamgi_math_matrix_absolute (base,
v1[0], v2[0], v3[0], v1[1], v2[1], v3[1], v1[2], v2[2], v3[2]);
gamgi_math_matrix_inverse (base, inverse);

gamgi_phys_cell_parallelepiped_range (cell->p1, cell->p2, cell->p3, v1, v2, v3, range);


cell->n_points = cell->n_nodes = n_nodes;
if (cell->borders == GAMGI_PHYS_EDGES) cell->n_points += 8;
points = (double *) malloc (cell->n_points * 3 * sizeof (double));
cell->points = points;


offset = 0;
for (i = range[4]; i <= range[5]; i++)
  {
  for (j = range[2]; j <= range[3]; j++)
    {
    for (k = range[0]; k <= range[1]; k++)
      {


      gamgi_math_vector_translation (k, j, i,
      cell->p1, cell->p2, cell->p3, position);

      if (gamgi_phys_cell_parallelepiped_inside (inverse, position) == TRUE)
        {
        gamgi_math_vector_copy (position, points + offset);
        offset += 3;
        }

      }
    }
  }

}
