static_light (gamgi_window *window, gamgi_bool global)
{
gamgi_layer *layer;
gamgi_object *object;
gamgi_dlist *dlist_w, *dlist_l;
GtkWidget *menu = NULL;

if (global == FALSE)
  { static_menu (window, window->layer->light_start); return; }

for (dlist_w = window->layer_start; dlist_w != NULL; dlist_w = dlist_w->next)
  {
  layer = GAMGI_CAST_LAYER dlist_w->data;
  for (dlist_l = layer->light_start; dlist_l != NULL; dlist_l = dlist_l->next)
    {
    object = GAMGI_CAST_OBJECT dlist_l->data;
    menu = static_item (menu, object, window);
    }
  }


if (menu != NULL)
  gtk_menu_popup ((GtkMenu *) menu, NULL, NULL, NULL, NULL, 1, 0);
}
