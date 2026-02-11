static_ok_global (gamgi_window *window_dialog)
{
gamgi_window *window_mouse;
gamgi_layer *layer;
gamgi_object *object;
gamgi_dlist *dlist;
gamgi_slist *start;

cache.local = FALSE;


if (gamgi->groups == NULL)
  { gamgi_gtk_dialog_message_create ("Error",
  "Empty list of group objects", window_dialog); return; }

if (static_grab (window_dialog) == FALSE) return;


layer = cache.layer;
if (layer == NULL)
  {


  gamgi_global_selection_undo ();
  gamgi_global_selection_focus ();
  }
else
  {


  gamgi_gtk_history_update (layer, layer->undo, GAMGI_ENGINE_UNDO);
  }


start = NULL;
for (dlist = gamgi->groups; dlist != NULL; dlist = dlist->next)
  if (static_apply (GAMGI_CAST_GROUP dlist->data, window_dialog) == FALSE)
    {
    start = gamgi_engine_slist_add_start (start);
    start->data = dlist->data;
    }
gamgi_io_error_list (start, window_dialog);

if (layer == NULL)
  {


  gamgi_mesa_draw_gamgi ();
  }
else
  {


  object = GAMGI_CAST_OBJECT gamgi->groups->data;
  gamgi_gtk_object_copy (object, GAMGI_CAST_OBJECT layer, window_dialog);


  window_mouse =  GAMGI_CAST_WINDOW layer->object.object;
  gtk_widget_queue_draw (window_mouse->area);
  }

static_reset (window_dialog);
}
