_cb_confirm_yes(void *data)
{
   E_Config_Dialog_Data *cfdata = NULL;

   if (!(cfdata = data)) return;
   cfdata->use_composite = 1;
}
