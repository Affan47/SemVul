_e_mod_action_cb_edge(E_Object *obj  __UNUSED__, const char *params, E_Event_Zone_Edge *ev)
{
   IF_RELEASE(_params);
   if (params && params[0])
     _params = eina_stringshare_add(params);

   if (_idler) ecore_idle_enterer_del(_idler);

   evry_show(ev->zone, ev->edge, _params, EINA_TRUE);
}
