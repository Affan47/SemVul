gamgi_phys_direction_vector (gamgi_cell *cell,
int *uvw, gamgi_enum vectors, double *vector)
{


if (vectors == GAMGI_PHYS_CONVENTIONAL)
  gamgi_math_vector_translation (uvw[0], uvw[1], uvw[2],
  cell->a1, cell->a2, cell->a3, vector);
if (vectors == GAMGI_PHYS_PRIMITIVE)
  gamgi_math_vector_translation (uvw[0], uvw[1], uvw[2],
  cell->p1, cell->p2, cell->p3, vector);
}
