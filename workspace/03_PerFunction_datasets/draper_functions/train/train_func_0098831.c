static_origin (gamgi_object *child, gamgi_object *parent)
{
gamgi_text *text;
gamgi_orbital *orbital;
gamgi_atom *atom;
gamgi_direction *direction;
gamgi_plane *plane;
gamgi_group *group;
gamgi_molecule *molecule;
gamgi_cluster *cluster;
gamgi_cell *cell;
gamgi_assembly *assembly;
gamgi_layer *layer;
double origin[3];


if (cache.child == TRUE)
  gamgi_mesa_translate_object (child, cache.origin);
else
  {


  switch (parent->class)
    {
    case GAMGI_ENGINE_CELL:
    cell = GAMGI_CAST_CELL parent;
    gamgi_math_vector_copy (cell->origin, origin);
    break;

    case GAMGI_ENGINE_ASSEMBLY:
    assembly = GAMGI_CAST_ASSEMBLY parent;
    gamgi_math_vector_copy (assembly->origin, origin);
    break;

    case GAMGI_ENGINE_LAYER:
    layer = GAMGI_CAST_LAYER parent;
    gamgi_math_vector_copy (layer->center, origin);
    break;
    }


  gamgi_math_vector_add (origin, cache.origin, origin);

  switch (child->class)
    {
    case GAMGI_ENGINE_TEXT:
    text = GAMGI_CAST_TEXT child;
    gamgi_math_vector_sub (origin, text->origin, origin);
    break;

    case GAMGI_ENGINE_ORBITAL:
    orbital = GAMGI_CAST_ORBITAL child;
    gamgi_math_vector_sub (origin, orbital->origin, origin);
    break;

    case GAMGI_ENGINE_ATOM:
    atom = GAMGI_CAST_ATOM child;
    gamgi_math_vector_sub (origin, atom->position, origin);
    break;

    case GAMGI_ENGINE_DIRECTION:
    direction = GAMGI_CAST_DIRECTION parent;
    gamgi_math_vector_sub (origin, direction->origin, origin);
    break;

    case GAMGI_ENGINE_PLANE:
    plane = GAMGI_CAST_PLANE parent;
    gamgi_math_vector_sub (origin, plane->origin, origin);
    break;

    case GAMGI_ENGINE_GROUP:
    group = GAMGI_CAST_GROUP parent;
    gamgi_math_vector_sub (origin, group->origin, origin);
    break;

    case GAMGI_ENGINE_MOLECULE:
    molecule = GAMGI_CAST_MOLECULE parent;
    gamgi_math_vector_sub (origin, molecule->origin, origin);
    break;

    case GAMGI_ENGINE_CLUSTER:
    cluster = GAMGI_CAST_CLUSTER parent;
    gamgi_math_vector_sub (origin, cluster->origin, origin);
    break;

    case GAMGI_ENGINE_CELL:
    cell = GAMGI_CAST_CELL parent;
    gamgi_math_vector_sub (origin, cell->origin, origin);
    break;
    }

  gamgi_mesa_translate_object (child, origin);
  }

}
