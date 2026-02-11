_elm_ews_border_sig_move_start(void *data, Evas_Object *o __UNUSED__, const char *sig __UNUSED__, const char *source __UNUSED__)
{
   Ecore_Evas *ee = data;
   Evas_Object *bs_o = ecore_evas_ews_backing_store_get(ee);
   int x, y, ox, oy;

   if (_ews_border_mover) ecore_animator_del(_ews_border_mover);

   evas_pointer_output_xy_get(evas_object_evas_get(bs_o), &x, &y);
   evas_object_geometry_get(bs_o, &ox, &oy, NULL, NULL);
   _ews_border_mover_off.x = x - ox;
   _ews_border_mover_off.y = y - oy;
   _ews_border_mover_obj = bs_o;
   _ews_border_mover = ecore_animator_add(_elm_ews_border_mover, ee);
}
