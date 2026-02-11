elm_map_zoom_min_set(Evas_Object *obj,
                     int zoom)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   ELM_MAP_CHECK(obj);
   ELM_MAP_DATA_GET(obj, sd);
   EINA_SAFETY_ON_NULL_RETURN(sd->src_tile);

   sd->zoom_min = zoom;
#else
   (void)obj;
   (void)zoom;
#endif
}
