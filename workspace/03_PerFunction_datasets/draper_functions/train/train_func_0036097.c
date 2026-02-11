e_modapi_init(E_Module *m)
{
   conf_item_edd = E_CONFIG_DD_NEW("Tasks_Config_Item", Config_Item);

#undef T
#undef D
#define T Config_Item
#define D conf_item_edd
   E_CONFIG_VAL(D, T, id, STR);
   E_CONFIG_VAL(D, T, show_all, INT);
   E_CONFIG_VAL(D, T, minw, INT);
   E_CONFIG_VAL(D, T, minh, INT);
   E_CONFIG_VAL(D, T, icon_only, UCHAR);
   E_CONFIG_VAL(D, T, text_only, UCHAR);

   conf_edd = E_CONFIG_DD_NEW("Tasks_Config", Config);

#undef T
#undef D
#define T Config
#define D conf_edd
   E_CONFIG_LIST(D, T, items, conf_item_edd);

   tasks_config = e_config_domain_load("module.tasks", conf_edd);
   if (!tasks_config)
     {
        Config_Item *config;

        tasks_config = E_NEW(Config, 1);

        config = E_NEW(Config_Item, 1);
        config->id = eina_stringshare_add("0");
        config->show_all = 0;
        config->minw = 100;
        config->minh = 32;
        tasks_config->items = eina_list_append(tasks_config->items, config);
     }

   tasks_config->module = m;

   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_ADD, _tasks_cb_event_border_add, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_REMOVE, _tasks_cb_event_border_remove, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_ICONIFY, _tasks_cb_event_border_iconify, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_UNICONIFY, _tasks_cb_event_border_uniconify, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_ICON_CHANGE, _tasks_cb_event_border_icon_change, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_DESK_SET, _tasks_cb_event_border_desk_set, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_ZONE_SET, _tasks_cb_event_border_zone_set, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_FOCUS_IN, _tasks_cb_window_focus_in, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_FOCUS_OUT, _tasks_cb_window_focus_out, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_PROPERTY, _tasks_cb_event_border_property, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_DESK_SHOW, _tasks_cb_event_desk_show, NULL));
   tasks_config->handlers = eina_list_append
       (tasks_config->handlers, ecore_event_handler_add
         (E_EVENT_BORDER_URGENT_CHANGE, _tasks_cb_event_border_urgent_change, NULL));

   tasks_config->borders = eina_list_clone(e_border_client_list());

   e_gadcon_provider_register(&_gadcon_class);
   return m;
}
