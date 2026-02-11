static_ok_local (gamgi_window *window_dialog)
{
gamgi_window *window_child, *window_parent;
gamgi_layer *layer_child, *layer_parent;
gamgi_bond *bond;
gamgi_object *child, *parent;
GtkWidget *dialog = window_dialog->dialog0;

cache.local = TRUE;


bond = GAMGI_CAST_BOND gamgi_gtk_object_name_number (dialog,
"entry_bond", GAMGI_ENGINE_BOND, window_dialog);
if (bond == NULL)
  {
  gamgi_gtk_dialog_message_create ("Error",
  "Invalid bond object", window_dialog);
  return;
  }

if (static_grab (window_dialog) == FALSE) return;

child = cache.object; parent = GAMGI_CAST_OBJECT bond;

layer_parent = gamgi_engine_find_layer (parent);
window_parent =  GAMGI_CAST_WINDOW layer_parent->object.object;
layer_child = gamgi_engine_find_layer (child);
window_child =  GAMGI_CAST_WINDOW layer_child->object.object;


if (child == window_child->focus)
  gamgi_gtk_object_focus_local (GAMGI_CAST_OBJECT
  window_child->layer, window_child);

static_apply (child, parent, layer_child, layer_parent, window_dialog);


gamgi_gtk_object_raise (layer_parent, window_parent);


gtk_widget_queue_draw (window_parent->area);
if (window_child != window_parent)
  gtk_widget_queue_draw (window_child->area);

static_clean (window_dialog);
}
