_cb_files_files_changed(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   const char *buf;
   const char *p;
   E_Config_Dialog_Data *cfdata;

   cfdata = data;
   if (!cfdata->imc_current) return;
   if (!cfdata->o_fm) return;
   p = e_fm2_real_path_get(cfdata->o_fm);
   if (p)
     {
        if (strncmp(p, cfdata->imc_current, strlen(p))) return;
     }

   buf = e_intl_imc_personal_path_get();
   if (!strncmp(cfdata->imc_current, buf, strlen(buf)))
     p = cfdata->imc_current + strlen(buf) + 1;
   else
     {
        buf = e_intl_imc_system_path_get();
        if (!strncmp(cfdata->imc_current, buf, strlen(buf)))
          p = cfdata->imc_current + strlen(buf) + 1;
     }
   if (!p) return;
   e_fm2_select_set(cfdata->o_fm, p, 1);
   e_fm2_file_show(cfdata->o_fm, p);
}
