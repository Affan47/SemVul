gamgi_math_measure_angle_2plane (gamgi_plane *plane1,
gamgi_plane *plane2, double *angle)
{
gamgi_cell *cell;
gamgi_object *object;
double normal1[3], normal2[3];
double pole[3], origin[3];


object = GAMGI_CAST_OBJECT plane1->object.object;
if (object->class != GAMGI_ENGINE_CELL) return FALSE;
cell = GAMGI_CAST_CELL object;

if (plane1->model == GAMGI_PHYS_VECTOR)
  {
  gamgi_math_cell_offset (cell, origin);
  gamgi_math_vector_sub (plane1->points, origin, pole);
  }
else gamgi_phys_plane_vector (cell, plane1->hkl, plane1->vectors, pole);

gamgi_math_cell_vector_rotate (cell, pole, normal1);


object = GAMGI_CAST_OBJECT plane2->object.object;
if (object->class != GAMGI_ENGINE_CELL) return FALSE;
cell = GAMGI_CAST_CELL object;

if (plane2->model == GAMGI_PHYS_VECTOR)
  {
  gamgi_math_cell_offset (cell, origin);
  gamgi_math_vector_sub (plane2->points, origin, pole);
  }
else gamgi_phys_plane_vector (cell, plane2->hkl, plane2->vectors, pole);

gamgi_math_cell_vector_rotate (cell, pole, normal2);

*angle = gamgi_math_vector_angle (normal1, normal2);

return TRUE;
}
