_elm_icon_signal_emit(Evas_Object *obj,
                      const char *emission,
                      const char *source)
{
   ELM_ICON_DATA_GET(obj, sd);

   if (!ELM_IMAGE_DATA(sd)->edje) return;

   edje_object_signal_emit(ELM_IMAGE_DATA(sd)->img, emission, source);
}
