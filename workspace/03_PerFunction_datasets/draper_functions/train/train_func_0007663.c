static_line (gamgi_direction *direction,
double thickness, double *position, double *normal, gamgi_dlist *dlist)
{
gamgi_atom *atom;
gamgi_darray *darray;
double point[4];
double r[3];
double length;


darray = gamgi_engine_darray_create (GAMGI_MATH_PLANE_SIZE, GAMGI_MATH_PLANE_STEP, 4);


while (dlist != NULL)
  {
  atom = GAMGI_CAST_ATOM dlist->data;

  gamgi_math_vector_sub (atom->position, position, point);
  length = gamgi_math_vector_dot (point, normal);
  gamgi_math_vector_scale (normal, r, length);
  gamgi_math_vector_sub (point, r, point);
  length = gamgi_math_vector_length (point);

  if (fabs (length) < thickness)
    {
    gamgi_math_vector_sub (atom->position, point, point);
    gamgi_engine_darray_push (darray, point);
    }

  dlist = dlist->next;
  }

return darray;
}
