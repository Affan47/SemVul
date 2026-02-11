_free_data(E_Config_Dialog *cfd  __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   Eina_Inlist *l;
   Config_Entry *ce;
   EINA_INLIST_FOREACH_SAFE(cfdata->entries, l, ce)
     _config_entry_free(ce);
   EINA_INLIST_FOREACH_SAFE(cfdata->transient_entries, l, ce)
     _config_entry_free(ce);
   free(cfdata);
   qa_mod->cfd = NULL;
}
