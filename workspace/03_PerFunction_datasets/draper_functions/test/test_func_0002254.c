_ecore_con_event_server_del_free(void *data __UNUSED__,
                                 void      *ev)
{
   Ecore_Con_Event_Server_Del *e;

   e = ev;
   if (e->server)
     {
        e->server->event_count = eina_list_remove(e->server->event_count, ev);
        if (!e->server->event_count)
          _ecore_con_server_free(e->server);
     }
   ecore_con_event_server_del_free(e);
   _ecore_con_event_count--;
   if ((!_ecore_con_event_count) && (!_ecore_con_init_count))
     ecore_con_mempool_shutdown();
}
