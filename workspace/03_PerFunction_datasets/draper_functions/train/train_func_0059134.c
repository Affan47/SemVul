static_ok_global (gamgi_window *window_dialog)
{
gamgi_window *window_parent;
gamgi_layer *layer_child, *layer_parent;
gamgi_object *child, *parent;
gamgi_dlist *dlist;
gamgi_slist *start;

cache.local = FALSE;


if (gamgi->texts == NULL)
  { gamgi_gtk_dialog_message_create ("Error",
  "Empty list of text objects", window_dialog); return; }

if (static_grab (window_dialog) == FALSE) return;


gamgi_global_selection_undo ();
gamgi_global_selection_focus ();

if (cache.above == TRUE)
  {


  parent = cache.object;
  layer_parent = gamgi_engine_find_layer (parent);

  start = NULL;
  for (dlist = gamgi->texts; dlist != NULL; dlist = dlist->next)
    {
    child = GAMGI_CAST_OBJECT dlist->data;
    layer_child = gamgi_engine_find_layer (child);

    if (static_apply (child, parent,
    layer_child, layer_parent, window_dialog) == FALSE)
      {
      start = gamgi_engine_slist_add_start (start);
      start->data = dlist->data;
      }
    }


  window_parent = GAMGI_CAST_WINDOW layer_parent->object.object;
  gamgi_gtk_object_raise (layer_parent, window_parent);
  }

if (cache.above == FALSE)
  {


  child = cache.object;

  start = NULL;
  for (dlist = gamgi->texts; dlist != NULL; dlist = dlist->next)
    {
    parent = GAMGI_CAST_OBJECT dlist->data;
    layer_parent = gamgi_engine_find_layer (parent);

    if (static_apply (child, parent,
    layer_parent, layer_parent, window_dialog) == FALSE)
      {
      start = gamgi_engine_slist_add_start (start);
      start->data = dlist->data;
      }
    }

  }

gamgi_io_error_list (start, window_dialog);

gamgi_mesa_draw_gamgi ();


static_reset (window_dialog);
}
