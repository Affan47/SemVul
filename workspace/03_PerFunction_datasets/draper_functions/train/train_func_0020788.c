elm_map_overlay_displayed_zoom_min_set(Elm_Map_Overlay *overlay,
                                       int zoom)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   EINA_SAFETY_ON_NULL_RETURN(overlay);
   EINA_SAFETY_ON_NULL_RETURN(overlay->wsd);
   ELM_MAP_CHECK(ELM_WIDGET_DATA(overlay->wsd)->obj);

   overlay->zoom_min = zoom;
   evas_object_smart_changed(overlay->wsd->pan_obj);
#else
   (void)overlay;
   (void)zoom;
#endif
}
