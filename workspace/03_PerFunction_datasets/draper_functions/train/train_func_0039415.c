gamgi_mesa_translate (gamgi_window *window,
gamgi_object *object, double *shift)
{


if (gamgi->focus != FALSE)
  { gamgi_mesa_translate_list (shift); return; }


switch (object->class)
  {


  case GAMGI_ENGINE_WINDOW:
  if (window->axes == FALSE)
    gamgi_mesa_translate_window_in (window, shift);
  else
    gamgi_mesa_translate_window_out (window, shift);
  break;


  case GAMGI_ENGINE_LAYER:
  if (window->axes == FALSE)
    gamgi_mesa_translate_layer_in (window->layer, object, shift);
  else
    gamgi_mesa_translate_layer_out (window->layer, shift);
  break;


  default:
  gamgi_mesa_translate_layer_in (window->layer, object, shift);
  break;
  }


gtk_widget_queue_draw (window->area);
}
