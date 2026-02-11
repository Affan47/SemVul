_e_fm2_uri_icon_list_get(Eina_List *uri)
{
   Eina_List *icons = NULL;
   Eina_List *l;
   const char *path;

   EINA_LIST_FOREACH(uri, l, path)
     {
        Evas_Object *fm;
        E_Fm2_Icon *ic;
        const char *file;

        ic = NULL;
        fm = _e_fm2_file_fm2_find(path);
        if (!fm) continue;
        file = ecore_file_file_get(path);
        ic = _e_fm2_icon_find(fm, file);
        icons = eina_list_append(icons, ic);
     }
   return icons;
}
