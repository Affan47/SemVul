e_container_border_stack_below(E_Border *bd, E_Border *below)
{
   int pos = 0, i;

   if (!bd->zone) return;

   for (i = 0; i < 11; i++)
     {
        bd->zone->container->layers[i].clients =
          eina_list_remove(bd->zone->container->layers[i].clients, bd);
     }


   bd->layer = below->layer;
   pos = _e_container_layer_map(bd->layer);

   ecore_x_window_configure(bd->win,
                            ECORE_X_WINDOW_CONFIGURE_MASK_SIBLING |
                            ECORE_X_WINDOW_CONFIGURE_MASK_STACK_MODE,
                            0, 0, 0, 0, 0,
                            below->win, ECORE_X_WINDOW_STACK_BELOW);

   bd->zone->container->layers[pos].clients =
     eina_list_prepend_relative(bd->zone->container->layers[pos].clients, bd, below);
}
