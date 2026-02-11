static_apply (gamgi_object *child, gamgi_object *parent,
gamgi_layer *layer_child, gamgi_layer *layer_parent, gamgi_window *window)
{


if (child->object == parent)
  {
  if (cache.local == TRUE)
    gamgi_gtk_dialog_message_create ("Error",
    "Child already linked to parent", window);
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


  if (child->class == parent->class &&
  gamgi_engine_find_object (parent, child) == TRUE)
    {
    gamgi_engine_unlink_object (parent);
    gamgi_engine_link_object_object (parent, child->object);
    }

  gamgi_engine_unlink_object (child);
  }

gamgi_engine_link_object_object (child, parent);


static_origin (child, parent);

return TRUE;
}
