_icon_freedesktop_set(Evas_Object *obj,
                      const char *name,
                      int size)
#else
_icon_freedesktop_set(Evas_Object * obj __UNUSED__,
                      const char *name __UNUSED__,
                      int size __UNUSED__)
#endif
{
#ifdef ELM_EFREET
   const char *path;

   ELM_ICON_DATA_GET(obj, sd);

   elm_need_efreet();

   if (icon_theme == NON_EXISTING) return EINA_FALSE;

   if (!icon_theme)
     {
        Efreet_Icon_Theme *theme;

        theme = efreet_icon_theme_find(getenv("E_ICON_THEME"));
        if (!theme)
          {
             const char **itr;
             static const char *themes[] = {
                "gnome", "Human", "oxygen", "hicolor", NULL
             };
             for (itr = themes; *itr; itr++)
               {
                  theme = efreet_icon_theme_find(*itr);
                  if (theme) break;
               }
          }

        if (!theme)
          {
             icon_theme = NON_EXISTING;
             return EINA_FALSE;
          }
        else
          icon_theme = eina_stringshare_add(theme->name.internal);
     }
   path = efreet_icon_path_find(icon_theme, name, size);
   sd->freedesktop.use = !!path;
   if (sd->freedesktop.use)
     {
        sd->freedesktop.requested_size = size;
        elm_image_file_set(obj, path, NULL);
        return EINA_TRUE;
     }
#endif
   return EINA_FALSE;
}
