_ilist_files_main_cb(void *data, Eio_File *handler, const char *file)
{
   E_Config_Dialog_Data *cfdata = data;

   if (handler == cfdata->eio[0])
     cfdata->personal_file_list = eina_list_append(cfdata->personal_file_list, eina_stringshare_add(file));
   else
     cfdata->system_file_list = eina_list_append(cfdata->system_file_list, eina_stringshare_add(file));
}
