_delayed_action_cb_timer(void *data)
{
   Delayed_Action *da;
   E_Action *act;

   da = data;
   da->timer = NULL;
   act = e_action_find(da->delayed.action);
   if (act)
     {
        if (act->func.go) act->func.go(da->obj, da->delayed.params);
     }
   _delayed_actions = eina_list_remove(_delayed_actions, da);
   _delayed_action_free(da);
   return ECORE_CALLBACK_CANCEL;
}
