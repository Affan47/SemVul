_e_mod_policy_cb_window_property(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   Ecore_X_Event_Window_Property *ev;

   ev = event;
   if ((_policy) && (_policy->funcs.property_change))
     _policy->funcs.property_change(ev);

   return ECORE_CALLBACK_PASS_ON;
}
