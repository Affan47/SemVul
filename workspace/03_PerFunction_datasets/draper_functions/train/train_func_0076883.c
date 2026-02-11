_ecore_ipc_event_client_del(void *data __UNUSED__, int ev_type __UNUSED__, void *ev)
{
   Ecore_Con_Event_Client_Del *e;
   Ecore_Ipc_Server *svr;

   e = ev;
   if (!e->client) return ECORE_CALLBACK_RENEW;
   svr = ecore_con_server_data_get(ecore_con_client_server_get(e->client));
   if (!eina_list_data_find(servers, svr)) return ECORE_CALLBACK_RENEW;

     {
        Ecore_Ipc_Client *cl;

        cl = ecore_con_client_data_get(e->client);
        cl->client = NULL;
          {
             Ecore_Ipc_Event_Client_Del *e2;

             if (!cl->delete_me)
               {
                  e2 = calloc(1, sizeof(Ecore_Ipc_Event_Client_Del));
                  if (e2)
                    {
                       cl->event_count++;
                       e2->client = cl;
                       ecore_event_add(ECORE_IPC_EVENT_CLIENT_DEL, e2,
                                       _ecore_ipc_event_client_del_free, NULL);
                    }
               }
          }
     }
   return ECORE_CALLBACK_CANCEL;
}
