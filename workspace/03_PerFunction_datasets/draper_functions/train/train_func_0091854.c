_cb_add(void *data, void *data2 __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;

   cfdata = data;
   if (!cfdata) return;

   if (cfdata->dia_new_profile)
     e_win_raise(cfdata->dia_new_profile->dia->win);
   else
     {
        cfdata->dia_new_profile = e_entry_dialog_show(_("Add New Profile"), NULL,
                                             _("Name:"), NULL, NULL, NULL,
                                             _new_profile_cb_ok,
                                             NULL, cfdata);
        e_object_data_set(E_OBJECT(cfdata->dia_new_profile), cfdata);
        e_object_del_attach_func_set(E_OBJECT(cfdata->dia_new_profile), _new_profile_cb_dia_del);
     }
}
