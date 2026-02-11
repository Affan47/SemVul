e_module_enable(E_Module *m)
{
   Eina_List *l;
   E_Event_Module_Update *ev;
   E_Config_Module *em;

   E_OBJECT_CHECK_RETURN(m, 0);
   E_OBJECT_TYPE_CHECK_RETURN(m, E_MODULE_TYPE, 0);
   if ((m->enabled) || (m->error)) return 0;
   m->data = m->func.init(m);
   if (m->data)
     {
        m->enabled = 1;
        EINA_LIST_FOREACH(e_config->modules, l, em)
          {
             if (!em) continue;
             if (!e_util_strcmp(em->name, m->name))
               {
                  em->enabled = 1;
                  e_config_save_queue();

                  ev = E_NEW(E_Event_Module_Update, 1);
                  ev->name = eina_stringshare_ref(em->name);
                  ev->enabled = 1;
                  ecore_event_add(E_EVENT_MODULE_UPDATE, ev,
                                  _e_module_event_update_free, NULL);
                  break;
               }
          }
        if (!_e_modules_initting)
          _e_module_whitelist_check();
        return 1;
     }
   return 0;
}
