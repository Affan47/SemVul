_elm_map_pan_smart_pos_set(Evas_Object *obj,
                           Evas_Coord x,
                           Evas_Coord y)
{
   ELM_MAP_PAN_DATA_GET(obj, psd);

   if ((x == psd->wsd->pan_x) && (y == psd->wsd->pan_y)) return;

   psd->wsd->pan_x = x;
   psd->wsd->pan_y = y;

   evas_object_smart_changed(obj);
}
