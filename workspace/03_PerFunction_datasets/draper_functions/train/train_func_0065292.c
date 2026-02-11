gamgi_engine_link_object_direction (gamgi_object *object, gamgi_direction *direction)
{


switch (object->class)
  {
  case GAMGI_ENGINE_TEXT:
  gamgi_engine_link_text_direction (GAMGI_CAST_TEXT object, direction);
  break;

  case GAMGI_ENGINE_ORBITAL:
  gamgi_engine_link_orbital_direction (GAMGI_CAST_ORBITAL object, direction);
  break;

  case GAMGI_ENGINE_ATOM:
  gamgi_engine_link_atom_direction (GAMGI_CAST_ATOM object, direction);
  break;

  default:
  break;
  }

}
