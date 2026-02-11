elm_map_overlay_data_get(const Elm_Map_Overlay *overlay)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   EINA_SAFETY_ON_NULL_RETURN_VAL(overlay, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(overlay->wsd, NULL);
   ELM_MAP_CHECK(ELM_WIDGET_DATA(overlay->wsd)->obj) NULL;

   return overlay->data;
#else
   (void)overlay;
   return NULL;
#endif
}
