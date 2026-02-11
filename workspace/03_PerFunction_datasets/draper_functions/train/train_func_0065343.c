gamgi_engine_link_object_group (gamgi_object *object, gamgi_group *group)
{


switch (object->class)
  {
  case GAMGI_ENGINE_TEXT:
  gamgi_engine_link_text_group (GAMGI_CAST_TEXT object, group);
  break;

  case GAMGI_ENGINE_ORBITAL:
  gamgi_engine_link_orbital_group (GAMGI_CAST_ORBITAL object, group);
  break;

  case GAMGI_ENGINE_ATOM:
  gamgi_engine_link_atom_group (GAMGI_CAST_ATOM object, group);
  break;

  case GAMGI_ENGINE_DIRECTION:
  gamgi_engine_link_direction_group (GAMGI_CAST_DIRECTION object, group);
  break;

  case GAMGI_ENGINE_PLANE:
  gamgi_engine_link_plane_group (GAMGI_CAST_PLANE object, group);
  break;

  case GAMGI_ENGINE_GROUP:
  gamgi_engine_link_group_group (GAMGI_CAST_GROUP object, group);
  break;

  default:
  break;
  }

}
