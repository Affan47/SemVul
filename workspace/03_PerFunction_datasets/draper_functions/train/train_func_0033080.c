static_apply (gamgi_object *child, gamgi_object *parent,
gamgi_layer *layer_child, gamgi_layer *layer_parent, gamgi_window *window_dialog)
{


if (child->object == parent)
  {
  if (cache.local == TRUE)
    gamgi_gtk_dialog_message_create ("Error",
    "Child already linked to parent", window_dialog);
  return FALSE;
  }


if (cache.local == TRUE)
  {
  gamgi_gtk_history_update (layer_parent, layer_parent->undo, GAMGI_ENGINE_UNDO);
  if (layer_child != layer_parent)
    gamgi_gtk_history_update (layer_child, layer_child->undo, GAMGI_ENGINE_UNDO);
  }

if (cache.local == FALSE && cache.above == FALSE)
  {


  child = gamgi_engine_copy_object (child);
  }
else
  {


  if (layer_parent != layer_child) gamgi_chem_bond_half_remove (child);

  gamgi_engine_unlink_object (child);
  }

gamgi_engine_link_object_object (child, parent);


static_origin (child, parent);

return TRUE;
}
