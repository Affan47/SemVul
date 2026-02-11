static_backward (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
gamgi_layer *layer_new, *layer_old;
gamgi_dlist *dlist;

dlist = window->history;
layer_old = GAMGI_CAST_LAYER dlist->data;
dlist = dlist->next;
if (dlist == NULL)
  {
  gamgi_gtk_dialog_beep ();
  return;
  }
window->history = dlist;
static_update (window);
layer_new = GAMGI_CAST_LAYER dlist->data;
window->layer = layer_new;
static_swap (layer_old, layer_new);
gtk_widget_queue_draw (window->area);
}
