_ecore_ipc_event_client_data_free(void *data __UNUSED__, void *ev)
{
   Ecore_Ipc_Event_Client_Data *e;

   e = ev;
   e->client->event_count--;
   if (e->data) free(e->data);
   if ((e->client->event_count == 0) && (e->client->delete_me))
     ecore_ipc_client_del(e->client);
   free(e);
}
