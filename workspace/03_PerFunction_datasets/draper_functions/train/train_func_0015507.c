_plugins_init(const Evry_API *_api)
{
   evry = _api;

   if (!evry->api_version_check(EVRY_API_VERSION))
     return EINA_FALSE;

   action_handler = evry->event_handler_add(EVRY_EVENT_ACTION_PERFORMED,
                                            _cb_action_performed, NULL);

   _plug = EVRY_PLUGIN_BASE("Calculator", _module_icon, EVRY_TYPE_TEXT,
                            _begin, _finish, _fetch);

   _plug->history = EINA_FALSE;
   _plug->async_fetch = EINA_TRUE;

   if (evry->plugin_register(_plug, EVRY_PLUGIN_SUBJECT, 0))
     {
        Plugin_Config *pc = _plug->config;
        pc->view_mode = VIEW_MODE_LIST;
        pc->trigger = eina_stringshare_add("=");
        pc->trigger_only = EINA_TRUE;
        pc->aggregate = EINA_FALSE;


     }

   return EINA_TRUE;
}
