_e_fm2_file_fm2_find(const char *file)
{
   char *dir;
   Eina_List *l;
   Evas_Object *obj;

   dir = ecore_file_dir_get(file);
   if (!dir) return NULL;
   EINA_LIST_FOREACH(_e_fm2_list, l, obj)
     {
        if ((_e_fm2_list_walking > 0) &&
            (eina_list_data_find(_e_fm2_list_remove, obj))) continue;
        if (!strcmp(e_fm2_real_path_get(obj), dir))
          {
             free(dir);
             return obj;
          }
     }
   free(dir);
   return NULL;
}
