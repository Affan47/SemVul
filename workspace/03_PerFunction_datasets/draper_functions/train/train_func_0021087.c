_cb_files_files_changed(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;
   char buf[4096];
   const char *p;
   size_t len;

   cfdata = data;
   if (!cfdata->splash) return;
   if (!cfdata->o_fm) return;
   p = e_fm2_real_path_get(cfdata->o_fm);
   if (p)
     {
        if (strncmp(p, cfdata->splash, strlen(p))) return;
     }
   len = e_user_dir_concat_static(buf, "themes");
   if (!p) return;
   if (!strncmp(cfdata->splash, buf, len))
     p = cfdata->splash + len + 1;
   else
     {
        len = e_prefix_data_concat_static(buf, "data/themes");
        if (!strncmp(cfdata->splash, buf, len))
          p = cfdata->splash + len + 1;
        else
          p = cfdata->splash;
     }
   e_fm2_select_set(cfdata->o_fm, p, 1);
   e_fm2_file_show(cfdata->o_fm, p);
}
