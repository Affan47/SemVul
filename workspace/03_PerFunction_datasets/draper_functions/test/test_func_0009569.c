_elm_icon_smart_memfile_set(Evas_Object *obj,
                            const void *img,
                            size_t size,
                            const char *format,
                            const char *key)
{
   ELM_ICON_DATA_GET(obj, sd);

   Eina_Bool ret;

   EINA_SAFETY_ON_NULL_RETURN_VAL(img, EINA_FALSE);
   EINA_SAFETY_ON_TRUE_RETURN_VAL(!size, EINA_FALSE);
   eina_stringshare_del(sd->stdicon);
   sd->stdicon = NULL;

   _edje_signals_free(sd);

   ret = _elm_icon_parent_sc->memfile_set(obj, img, size, format, key);

   return ret;
}
