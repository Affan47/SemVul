gamgi_mesa_select_object (gamgi_window *window, int x, int y,
gamgi_enum class, gamgi_bool global, gamgi_function2 function)
{
gamgi_object *object;


if (function == NULL)
  gamgi->function = static_select;
else
  gamgi->function = function;


switch (class)
  {
  case GAMGI_ENGINE_GAMGI:
  break;

  case GAMGI_ENGINE_WINDOW:
  static_window (window, gamgi->window_start);
  break;

  case GAMGI_ENGINE_LAYER:
  static_menu (window, window->layer_start);
  break;

  case GAMGI_ENGINE_LIGHT:
  static_light (window, global);
  break;

  case GAMGI_ENGINE_ASSEMBLY: case GAMGI_ENGINE_CLUSTER:
  case GAMGI_ENGINE_GROUP: case GAMGI_ENGINE_TEXT:
  static_recursive (x, y, class, global, window);
  break;

  default:
  object = static_pick_objects (x, y, class, global, window);
  if (object != NULL) static_apply (object, window);
  break;
  }


window->class = FALSE;
}
