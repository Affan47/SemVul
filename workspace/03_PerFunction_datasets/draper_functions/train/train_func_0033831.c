static_polygon_array (gamgi_plane *plane,
int n_neighbours, gamgi_atom **neighbours)
{
gamgi_atom *atom;
gamgi_darray *darray;
int i;


darray = gamgi_engine_darray_create (GAMGI_MATH_PLANE_SIZE,
GAMGI_MATH_PLANE_STEP, 4);


for (i = 0; i < n_neighbours; i++)
  {


  atom = neighbours[i];
  gamgi_engine_darray_push (darray, atom->position);
  }

return darray;
}
