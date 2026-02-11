evry_plug_collection_shutdown(void)
{
   Evry_Plugin *p;

   EINA_LIST_FREE (plugins, p)
     {
        if (p->config_path)
          {
             e_configure_registry_item_del(p->config_path);
             eina_stringshare_del(p->config_path);
          }

        EVRY_PLUGIN_FREE(p);
     }
}
