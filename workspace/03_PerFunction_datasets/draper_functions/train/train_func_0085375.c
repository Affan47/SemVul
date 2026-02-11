e_shelf_popup_set(E_Shelf *es, int popup)
{

   E_OBJECT_CHECK(es);
   E_OBJECT_TYPE_CHECK(es, E_SHELF_TYPE);

   if (!es->cfg) return;
   if (((popup) && (es->popup)) || ((!popup) && (!es->popup))) return;

   if (popup)
     {
        evas_object_clip_unset(es->o_base);
        es->popup = e_popup_new(es->zone, es->x, es->y, es->w, es->h);
        e_popup_name_set(es->popup, "shelf");
        e_popup_layer_set(es->popup, es->cfg->layer);

        es->ee = es->popup->ecore_evas;
        es->evas = es->popup->evas;
        evas_object_show(es->o_event);
        evas_object_show(es->o_base);
        e_popup_edje_bg_object_set(es->popup, es->o_base);
        ecore_x_netwm_window_type_set(es->popup->evas_win,
                                      ECORE_X_WINDOW_TYPE_DOCK);

        e_drop_xdnd_register_set(es->popup->evas_win, 1);
        e_gadcon_xdnd_window_set(es->gadcon, es->popup->evas_win);
        e_gadcon_dnd_window_set(es->gadcon, es->popup->evas_win);
     }
   else
     {
        e_drop_xdnd_register_set(es->popup->evas_win, 0);
        e_object_del(E_OBJECT(es->popup));
        es->popup = NULL;

        es->ee = es->zone->container->bg_ecore_evas;
        es->evas = es->zone->container->bg_evas;

        evas_object_move(es->o_event, es->zone->x + es->x, es->zone->y + es->y);
        evas_object_move(es->o_base, es->zone->x + es->x, es->zone->y + es->y);
        evas_object_layer_set(es->o_event, es->cfg->layer);
        evas_object_layer_set(es->o_base, es->cfg->layer);

        e_drop_xdnd_register_set(es->zone->container->bg_win, 1);
        e_gadcon_xdnd_window_set(es->gadcon, es->zone->container->bg_win);
        e_gadcon_dnd_window_set(es->gadcon, es->zone->container->event_win);
        evas_object_clip_set(es->o_base, es->zone->bg_clip_object);
     }
}
