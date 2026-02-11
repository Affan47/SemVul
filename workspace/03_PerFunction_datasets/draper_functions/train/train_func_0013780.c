e_gadcon_client_edit_end(E_Gadcon_Client *gcc)
{
   Eina_List *l = NULL;
   E_Gadcon_Client *client = NULL;

   E_OBJECT_CHECK(gcc);
   E_OBJECT_TYPE_CHECK(gcc, E_GADCON_CLIENT_TYPE);

   if (gcc->o_frame)
     {
        evas_object_event_callback_del(gcc->o_frame, EVAS_CALLBACK_MOVE,
                                       _e_gadcon_cb_client_move);
        evas_object_event_callback_del(gcc->o_frame, EVAS_CALLBACK_RESIZE,
                                       _e_gadcon_cb_client_resize);
     }
   else if (gcc->o_base)
     {
        evas_object_event_callback_del(gcc->o_base, EVAS_CALLBACK_MOVE,
                                       _e_gadcon_cb_client_move);
        evas_object_event_callback_del(gcc->o_base, EVAS_CALLBACK_RESIZE,
                                       _e_gadcon_cb_client_resize);
     }

   if (gcc->moving)
     {
        gcc->moving = 0;
        if (gcc->cf) _e_gadcon_client_save(gcc);
     }
   if (gcc->o_event) evas_object_del(gcc->o_event);
   gcc->o_event = NULL;
   if (gcc->o_control) evas_object_del(gcc->o_control);
   gcc->o_control = NULL;

   e_gadcon_locked_set(gcc->gadcon, 0);
   EINA_LIST_FOREACH(gcc->gadcon->clients, l, client)
     {
        if (!client) continue;
        if (client->o_control) return;
     }
   gcc->gadcon->editing = 0;
}
