_e_ipc_cb_client_del(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   Ecore_Ipc_Event_Client_Del *e;

   e = event;
   if (ecore_ipc_client_server_get(e->client) != _e_ipc_server)
     return ECORE_CALLBACK_PASS_ON;

   e_thumb_client_del(e);
   e_fm2_client_del(e);
   e_init_client_del(e);
   ecore_ipc_client_del(e->client);
   return ECORE_CALLBACK_PASS_ON;
}
