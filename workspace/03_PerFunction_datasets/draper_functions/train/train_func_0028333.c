_elm_theme_icon_set(Elm_Theme *th,
                    Evas_Object *o,
                    const char *group,
                    const char *style)
{
   const char *file;
   char buf2[1024];
   int w, h;

   if (!th) th = &(theme_default);
   snprintf(buf2, sizeof(buf2), "elm/icon/%s/%s", group, style);
   file = _elm_theme_group_file_find(th, buf2);
   if (file)
     {
        elm_image_file_set(o, file, buf2);
        elm_image_object_size_get(o, &w, &h);
        if (w > 0) return EINA_TRUE;
     }
   snprintf(buf2, sizeof(buf2), "elm/icon/%s/default", group);
   file = _elm_theme_group_file_find(th, buf2);

   if (!file) return EINA_FALSE;

   elm_image_file_set(o, file, buf2);
   elm_image_object_size_get(o, &w, &h);

   return w > 0;
}
