_free_data(E_Config_Dialog *cfd __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   Efreet_Desktop *desk;

   EINA_LIST_FREE(cfdata->desks, desk)
     efreet_desktop_free(desk);
   if (cfdata->desk_change_handler)
     ecore_event_handler_del(cfdata->desk_change_handler);
   E_FREE(cfdata);
}
