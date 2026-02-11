_basic_apply(E_Config_Dialog *dialog, E_Config_Dialog_Data *cfdata)
{
   E_Mixer_Module_Context *ctxt = dialog->data;
   ctxt->default_instance = eina_list_nth(ctxt->instances,
                                          cfdata->default_instance);
   if (ctxt->default_instance)
     {
        E_Mixer_Module_Config *conf;
        const char *id;

        conf = ctxt->conf;
        if (conf->default_gc_id)
          eina_stringshare_del(conf->default_gc_id);

        id = ctxt->default_instance->gcc->cf->id;
        conf->default_gc_id = eina_stringshare_add(id);

        conf->desktop_notification = ctxt->desktop_notification;
     }

   return 1;
}
