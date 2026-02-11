_e_manager_cb_client_message(void *data __UNUSED__, int ev_type __UNUSED__, void *ev)
{
   Ecore_X_Event_Client_Message *e;
   E_Border *bd;

   e = ev;

   if (e->message_type != ECORE_X_ATOM_NET_ACTIVE_WINDOW) return ECORE_CALLBACK_RENEW;
   bd = e_border_find_by_client_window(e->win);
   if (!bd) return ECORE_CALLBACK_RENEW;
#if 0
   if (e->data.l[0] == 0 )
     {
     }
   timestamp = e->data.l[1];
   requestor_id e->data.l[2];
#endif
   switch (e_config->window_activehint_policy)
     {
      case 0: break;
      case 1:
        edje_object_signal_emit(bd->bg_object, "e,state,urgent", "e");
        break;
      default:
        if (!bd->focused) e_border_activate(bd, EINA_FALSE);
        else e_border_raise(bd);
     }

   return ECORE_CALLBACK_PASS_ON;
}
