static_export (static_polytope *polytope)
{
gamgi_group *group;
gamgi_atom *atom;
double unit[9], rotation[9];
double zero[3], translation[3];
int *index;
int i;


if (polytope->global == TRUE)
  group = gamgi_engine_copy_group (polytope->group);
else
  group = polytope->group;

if (group->object.object == NULL)
  gamgi_engine_link_object_object (GAMGI_CAST_OBJECT group, polytope->parent);


gamgi_math_vector_zero (zero);
gamgi_math_position_group_rotation_set (group, zero);
gamgi_math_position_group_translation_set (group, zero);

gamgi_math_position_rotation (group->object.object, rotation);
gamgi_math_position_translation (group->object.object, translation);

gamgi_math_vector_zero (zero);
gamgi_math_matrix_unit (unit);
gamgi_math_position_object_rotation (group->object.object, unit);
gamgi_math_position_object_translation (group->object.object, zero);


index = static_export_points (group, polytope);
static_export_loops (index, group, polytope);
free (index);


if (polytope->structure == GAMGI_CHEM_STRUCTURE_COPY)
  {


  atom = gamgi_engine_copy_atom (polytope->atom);
  gamgi_engine_link_atom_group (atom, group);
  for (i = 0; i < polytope->n_neighbours; i++)
    {
    atom = gamgi_engine_copy_atom (polytope->neighbours[i]);
    gamgi_engine_link_atom_group (atom, group);
    }

  gamgi_chem_atom_clean (polytope->atom);
  for (i = 0; i < polytope->n_neighbours; i++)
    gamgi_chem_atom_clean (polytope->neighbours[i]);
  }

if (polytope->structure == GAMGI_CHEM_STRUCTURE_LINK)
  {


  gamgi_engine_unlink_atom (polytope->atom);
  gamgi_engine_link_atom_group (polytope->atom, group);
  for (i = 0; i < polytope->n_neighbours; i++)
    {
    gamgi_engine_unlink_atom (polytope->neighbours[i]);
    gamgi_engine_link_atom_group (polytope->neighbours[i], group);
    }
  }


gamgi_math_position_object_rotation (group->object.object, rotation);
gamgi_math_position_object_translation (group->object.object, translation);
}
