elm_map_overlay_class_zoom_max_get(const Elm_Map_Overlay *klass)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   const Overlay_Class *ovl;

   EINA_SAFETY_ON_NULL_RETURN_VAL(klass, OVERLAY_CLASS_ZOOM_MAX);
   EINA_SAFETY_ON_NULL_RETURN_VAL(klass->wsd, OVERLAY_CLASS_ZOOM_MAX);
   ELM_MAP_CHECK(ELM_WIDGET_DATA(klass->wsd)->obj) OVERLAY_CLASS_ZOOM_MAX;

   EINA_SAFETY_ON_FALSE_RETURN_VAL
     (klass->type == ELM_MAP_OVERLAY_TYPE_CLASS, OVERLAY_CLASS_ZOOM_MAX);

   ovl = klass->ovl;
   return ovl->zoom_max;
#else
   (void)klass;
   return OVERLAY_CLASS_ZOOM_MAX;
#endif
}
