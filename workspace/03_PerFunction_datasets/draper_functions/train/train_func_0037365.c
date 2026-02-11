ecore_con_event_client_add(Ecore_Con_Client *cl)
{
   Ecore_Con_Event_Client_Add *e;
   int ev = ECORE_CON_EVENT_CLIENT_ADD;

   e = ecore_con_event_client_add_alloc();
   EINA_SAFETY_ON_NULL_RETURN(e);

   cl->event_count = eina_list_append(cl->event_count, e);
   cl->host_server->event_count = eina_list_append(cl->host_server->event_count, e);
   _ecore_con_cl_timer_update(cl);
   e->client = cl;
   if (cl->upgrade) ev = ECORE_CON_EVENT_CLIENT_UPGRADE;
   ecore_event_add(ev, e,
                   (Ecore_End_Cb)_ecore_con_event_client_add_free, cl->host_server);
   _ecore_con_event_count++;
}
