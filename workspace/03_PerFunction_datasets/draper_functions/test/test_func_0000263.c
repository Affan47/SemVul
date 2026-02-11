_ecore_con_event_client_data_free(Ecore_Con_Server *svr,
                                  void      *ev)
{
   Ecore_Con_Event_Client_Data *e;

   e = ev;
   if (e->client)
     {
        Eina_Bool svrfreed = EINA_FALSE;

        e->client->event_count = eina_list_remove(e->client->event_count, e);
        if (e->client->host_server)
          {
             e->client->host_server->event_count = eina_list_remove(e->client->host_server->event_count, ev);
          }
        if ((!svr->event_count) && (svr->delete_me))
          {
             _ecore_con_server_free(svr);
             svrfreed = EINA_TRUE;
          }
        if (!svrfreed)
          {
             if (((!e->client->event_count) && (e->client->delete_me)) ||
                 ((e->client->host_server &&
                   ((e->client->host_server->type & ECORE_CON_TYPE) == ECORE_CON_REMOTE_UDP ||
                       (e->client->host_server->type & ECORE_CON_TYPE) == ECORE_CON_REMOTE_MCAST))))
               ecore_con_client_del(e->client);
          }
     }
   free(e->data);
   ecore_con_event_client_data_free(e);
   _ecore_con_event_count--;
   if ((!_ecore_con_event_count) && (!_ecore_con_init_count))
     ecore_con_mempool_shutdown();
}
