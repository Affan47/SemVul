gamgi_phys_plane_polytope (int n_neighbours, gamgi_atom **neighbours,
gamgi_enum structure, float red, float green, float blue, gamgi_object *parent,
gamgi_atom *central)
{
gamgi_plane *plane;
gamgi_atom *atom;
gamgi_darray *darray;
double unit[9], rotation[9];
double zero[3], normal[3], translation[3];
int i;


plane = gamgi_engine_create_plane ();
gamgi_engine_start_plane (plane);
gamgi_engine_link_object_object (GAMGI_CAST_OBJECT plane, parent);
strcpy (plane->object.name, "Plane");

plane->reference = GAMGI_ENGINE_ATOM;
plane->model = GAMGI_PHYS_POLYGON;

plane->red = red;
plane->green = green;
plane->blue = blue;


gamgi_math_vector_zero (zero);
gamgi_math_matrix_unit (unit);

gamgi_math_position_plane_rotation_set (plane, zero);
gamgi_math_position_plane_translation_set (plane, zero);

gamgi_math_position_rotation (parent, rotation);
gamgi_math_position_translation (parent, translation);

gamgi_math_position_object_rotation (parent, unit);
gamgi_math_position_object_translation (parent, zero);


gamgi_math_polygon_normal (neighbours[0]->position,
neighbours[1]->position, neighbours[2]->position, normal);

darray = static_polygon_array (plane, n_neighbours, neighbours);

gamgi_math_polygon_orientate (darray, normal);
gamgi_math_polygon_convex (darray, normal);


gamgi_engine_darray_copy_remove (darray, &plane->points, &plane->n_points);
gamgi_math_polygon_loops (plane->n_points, &plane->loops, &plane->n_loops);
static_center (plane);


if (structure == GAMGI_CHEM_STRUCTURE_COPY)
  {


  atom = gamgi_engine_copy_atom (central);
  gamgi_engine_link_atom_plane (atom, plane);
  for (i = 0; i < n_neighbours; i++)
    {
    atom = gamgi_engine_copy_atom (neighbours[i]);
    gamgi_engine_link_atom_plane (atom, plane);
    }

  gamgi_chem_atom_clean (central);
  for (i = 0; i < n_neighbours; i++)
    gamgi_chem_atom_clean (neighbours[i]);
  }

if (structure == GAMGI_CHEM_STRUCTURE_LINK)
  {


  gamgi_engine_unlink_atom (central);
  gamgi_engine_link_atom_plane (central, plane);
  for (i = 0; i < n_neighbours; i++)
    {
    gamgi_engine_unlink_atom (neighbours[i]);
    gamgi_engine_link_atom_plane (neighbours[i], plane);
    }
  }


gamgi_math_position_object_rotation (plane->object.object, rotation);
gamgi_math_position_object_translation (plane->object.object, translation);
}
