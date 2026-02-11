_content_get(void *data, Evas_Object *obj, const char *source)
{
   if (!strcmp(source, "elm.swallow.icon"))
     {
        Evas_Object *ic;

        ic = elm_icon_add(obj);
        if (ecore_file_is_dir((char *)data))
          elm_icon_standard_set(ic, "folder");
        else
          elm_icon_standard_set(ic, "file");
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        evas_object_show(ic);
        return ic;
     }
   return NULL;
}
