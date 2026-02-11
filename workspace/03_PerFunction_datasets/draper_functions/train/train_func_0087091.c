_elm_image_smart_memfile_set(Evas_Object *obj,
                             const void *img,
                             size_t size,
                             const char *format,
                             const char *key)
{
   ELM_IMAGE_DATA_GET(obj, sd);

   _elm_image_file_set_do(obj);

   evas_object_image_memfile_set
     (sd->img, (void *)img, size, (char *)format, (char *)key);

   sd->preloading = EINA_TRUE;
   sd->show = EINA_TRUE;

   evas_object_hide(sd->img);
   evas_object_image_preload(sd->img, EINA_FALSE);
   if (evas_object_image_load_error_get(sd->img) != EVAS_LOAD_ERROR_NONE)
     {
        ERR("Things are going bad for some random " FMT_SIZE_T
            " byte chunk of memory (%p)", size, sd->img);
        return EINA_FALSE;
     }

   _elm_image_internal_sizing_eval(sd);

   return EINA_TRUE;
}
