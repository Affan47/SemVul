gamgi_engine_remove_object (gamgi_object *object)
{
switch (object->class)
  {
  case GAMGI_ENGINE_TEXT:
  gamgi_engine_remove_text (GAMGI_CAST_TEXT object);
  break;

  case GAMGI_ENGINE_ORBITAL:
  gamgi_engine_remove_orbital (GAMGI_CAST_ORBITAL object);
  break;

  case GAMGI_ENGINE_BOND:
  gamgi_engine_remove_bond (GAMGI_CAST_BOND object);
  break;

  case GAMGI_ENGINE_ATOM:
  gamgi_engine_remove_atom (GAMGI_CAST_ATOM object);
  break;

  case GAMGI_ENGINE_DIRECTION:
  gamgi_engine_remove_direction (GAMGI_CAST_DIRECTION object);
  break;

  case GAMGI_ENGINE_PLANE:
  gamgi_engine_remove_plane (GAMGI_CAST_PLANE object);
  break;

  case GAMGI_ENGINE_GROUP:
  gamgi_engine_remove_group (GAMGI_CAST_GROUP object);
  break;

  case GAMGI_ENGINE_MOLECULE:
  gamgi_engine_remove_molecule (GAMGI_CAST_MOLECULE object);
  break;

  case GAMGI_ENGINE_CLUSTER:
  gamgi_engine_remove_cluster (GAMGI_CAST_CLUSTER object);
  break;

  case GAMGI_ENGINE_CELL:
  gamgi_engine_remove_cell (GAMGI_CAST_CELL object);
  break;

  case GAMGI_ENGINE_ARROW:
  gamgi_engine_remove_arrow (GAMGI_CAST_ARROW object);
  break;

  case GAMGI_ENGINE_SHAPE:
  gamgi_engine_remove_shape (GAMGI_CAST_SHAPE object);
  break;

  case GAMGI_ENGINE_GRAPH:
  gamgi_engine_remove_graph (GAMGI_CAST_GRAPH object);
  break;

  case GAMGI_ENGINE_ASSEMBLY:
  gamgi_engine_remove_assembly (GAMGI_CAST_ASSEMBLY object);
  break;

  case GAMGI_ENGINE_LIGHT:
  gamgi_engine_remove_light (GAMGI_CAST_LIGHT object);
  break;

  case GAMGI_ENGINE_LAYER:
  gamgi_engine_remove_layer (GAMGI_CAST_LAYER object);
  break;

  case GAMGI_ENGINE_WINDOW:
  gamgi_engine_remove_window (GAMGI_CAST_WINDOW object);
  break;
  }
}
