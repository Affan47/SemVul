_imc_import_cb_changed(void *data, Evas_Object *obj __UNUSED__)
{
   Import *import;
   const char *path;
   const char *file;

   if (!(import = data)) return;
   if (!import->fsel_obj) return;

   path = e_widget_fsel_selection_path_get(import->fsel_obj);
   E_FREE(import->cfdata->file);
   if (path)
     import->cfdata->file = strdup(path);

   if (import->cfdata->file)
     {
        char *strip;

        file = ecore_file_file_get(import->cfdata->file);
        strip = ecore_file_strip_ext(file);
        if (!strip)
          {
             E_FREE(import->cfdata->file);
             e_widget_disabled_set(import->ok_obj, 1);
             return;
          }
        free(strip);
        if (!e_util_glob_case_match(file, "*.imc"))
          {
             E_FREE(import->cfdata->file);
             e_widget_disabled_set(import->ok_obj, 1);
             return;
          }
        e_widget_disabled_set(import->ok_obj, 0);
     }
   else
     e_widget_disabled_set(import->ok_obj, 1);
}
