static_ok_local (gamgi_window *window_dialog)
{
gamgi_window *window_child, *window_parent;
gamgi_layer *layer_child, *layer_parent;
gamgi_light *light;
gamgi_object *child, *parent;
GtkWidget *dialog = window_dialog->dialog0;

cache.local = TRUE;


light = GAMGI_CAST_LIGHT gamgi_gtk_object_name_number (dialog,
"entry_light", GAMGI_ENGINE_LIGHT, window_dialog);
if (light == NULL)
  {
  gamgi_gtk_dialog_message_create ("Error",
  "Invalid light object", window_dialog);
  return;
  }

if (static_grab (window_dialog) == FALSE) return;

parent = cache.object;
child = GAMGI_CAST_OBJECT light;

layer_parent = GAMGI_CAST_LAYER parent;
window_parent =  GAMGI_CAST_WINDOW parent->object;
layer_child = GAMGI_CAST_LAYER child->object;
window_child =  GAMGI_CAST_WINDOW layer_child->object.object;


if (child == window_child->focus)
  gamgi_gtk_object_focus_local (GAMGI_CAST_OBJECT
  window_child->layer, window_child);

static_apply (child, parent, layer_child, layer_parent, window_dialog);


gamgi_gtk_object_raise (layer_parent, window_parent);


gtk_widget_queue_draw (window_parent->area);
if (window_child != window_parent)
  gtk_widget_queue_draw (window_child->area);

static_reset (window_dialog);
}
