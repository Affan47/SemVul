_imc_import_cb_ok(void *data, void *data2 __UNUSED__)
{
   Import *import;
   E_Win *win;
   const char *path;
   const char *file;

   win = data;
   if (!(import = win->data)) return;

   path = e_widget_fsel_selection_path_get(import->fsel_obj);
   E_FREE(import->cfdata->file);
   if (path)
     import->cfdata->file = strdup(path);

   if (import->cfdata->file)
     {
        Eet_File *ef;
        E_Input_Method_Config *imc;
        char *strip;

        file = ecore_file_file_get(import->cfdata->file);

        if (!(strip = ecore_file_strip_ext(file))) return;
        free(strip);

        if (!e_util_glob_case_match(file, "*.imc"))
          return;

        imc = NULL;
        ef = eet_open(import->cfdata->file, EET_FILE_MODE_READ);
        if (ef)
          {
             imc = e_intl_input_method_config_read(ef);
             eet_close(ef);
          }

        if (!imc)
          {
             e_util_dialog_show(_("Input Method Config Import Error"),
                                _("Enlightenment was unable to import "
                                  "the configuration.<br><br>Are "
                                  "you sure this is really a valid "
                                  "configuration?"));
          }
        else
          {
             char buf[PATH_MAX];

             e_intl_input_method_config_free(imc);
             snprintf(buf, sizeof(buf), "%s/%s",
                      e_intl_imc_personal_path_get(), file);

             if (!ecore_file_cp(import->cfdata->file, buf))
               {
                  e_util_dialog_show(_("Input Method Config Import Error"),
                                     _("Enlightenment was unable to import "
                                       "the configuration<br>due to a copy "
                                       "error."));
               }
             else
               e_int_config_imc_update(import->parent, buf);
          }
     }

   e_int_config_imc_import_del(import->win);
}
