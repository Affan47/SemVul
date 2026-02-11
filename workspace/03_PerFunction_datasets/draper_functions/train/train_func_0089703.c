_advanced_apply_data(E_Config_Dialog *cfd  __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   Config_Entry *ce;
   Eina_Bool entry_changed = EINA_FALSE, transient_changed = EINA_FALSE;
#define SET(X) qa_config->X = cfdata->X

   SET(dont_bug_me);
   SET(first_run);

   EINA_INLIST_FOREACH(cfdata->entries, ce)
     {
        if (!ce->id) continue;
        if (!e_qa_entry_rename(ce->entry, ce->id))
          entry_changed = EINA_TRUE;
        eina_stringshare_replace(&ce->id, NULL);
     }
   EINA_INLIST_FOREACH(cfdata->transient_entries, ce)
     {
        if (!ce->id) continue;
        if (!e_qa_entry_rename(ce->entry, ce->id))
          transient_changed = EINA_TRUE;
        eina_stringshare_replace(&ce->id, NULL);
     }
   if (entry_changed)
     {
        e_widget_ilist_clear(cfdata->o_list_entry);
        _list_fill(qa_mod->cfd->cfdata, cfdata->o_list_entry, EINA_FALSE);
     }
   if (transient_changed)
     {
        e_widget_ilist_clear(cfdata->o_list_transient);
        _list_fill(qa_mod->cfd->cfdata, cfdata->o_list_transient, EINA_TRUE);
     }
   e_config_save_queue();
   return 1;
}
