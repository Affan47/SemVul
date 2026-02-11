gamgi_math_measure_length_atom_plane (gamgi_atom *atom,
gamgi_plane *plane, double *length)
{
gamgi_cell *cell;
gamgi_object *object;
double pole[3], normal[3];
double translate[3], origin[3];
double r1[3];


if (plane->model == GAMGI_PHYS_POLYGON)
  {


  gamgi_math_vector_sub (atom->position, plane->center, translate);
  gamgi_phys_plane_normal (plane, normal);
  *length = fabs (gamgi_math_vector_dot (translate, normal));
  }
else
  {


  object = GAMGI_CAST_OBJECT plane->object.object;
  if (object->class != GAMGI_ENGINE_CELL) return FALSE;
  cell = GAMGI_CAST_CELL object;

  if (plane->model == GAMGI_PHYS_VECTOR)
    {


    gamgi_phys_plane_point (plane, cell, r1);
    gamgi_math_vector_sub (atom->position, r1, translate);
    *length = gamgi_math_vector_length (translate);
    }
  else
    {


    gamgi_phys_plane_vector (cell, plane->hkl, plane->vectors, pole);
    gamgi_math_cell_vector_rotate (cell, pole, normal);

    gamgi_math_position_cell_translation_get (cell, origin);
    gamgi_math_vector_sub (atom->position, origin, translate);
    *length = fabs (gamgi_math_vector_dot (translate, normal));
    }
  }

return TRUE;
}
