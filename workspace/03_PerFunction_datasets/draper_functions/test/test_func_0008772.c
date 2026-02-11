gamgi_global_selection_undo (void)
{
gamgi_window *window;
gamgi_layer *layer;
gamgi_dlist *dlist;


for (window = gamgi->window_start; window != NULL; window = window->next)
  {
  for (dlist = window->layer_start; dlist != NULL; dlist = dlist->next)
    {
    layer = GAMGI_CAST_LAYER dlist->data;
    gamgi_gtk_history_update (layer, layer->undo, GAMGI_ENGINE_UNDO);
    }
  }
}
