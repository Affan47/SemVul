_free_data(E_Config_Dialog *cfd __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   cfdata->tbar->cfg_dlg = NULL;
   E_FREE(cfdata);
}
