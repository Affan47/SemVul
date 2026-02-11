_dia_del(void *data)
{
   E_Config_Dialog_Data *cfdata;

   cfdata = e_object_data_get(data);
   if (!cfdata) return;
   cfdata->locals.dia = NULL;
}
