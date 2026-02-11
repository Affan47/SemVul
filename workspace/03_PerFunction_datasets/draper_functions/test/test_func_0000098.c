_dia_del(void *data)
{
   E_Dialog *dia = data;
   E_Config_Dialog_Data *cfdata;

   cfdata = dia->data;
   if (!cfdata) return;
   cfdata->gui.fsel = NULL;
   cfdata->gui.fsel_wid = NULL;
}
