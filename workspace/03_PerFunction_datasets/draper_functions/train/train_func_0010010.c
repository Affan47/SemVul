evas_object_smart_clipped_smart_add(Evas_Object *obj)
{
   Evas_Object_Smart_Clipped_Data *cso;
   Evas_Object *clipper;

   cso = evas_object_smart_data_get(obj);
   if (!cso)
     cso = calloc(1, sizeof(*cso));

   cso->evas = evas_object_evas_get(obj);
   clipper = evas_object_rectangle_add(cso->evas);
   evas_object_static_clip_set(clipper, 1);
   cso->clipper = NULL;
   evas_object_smart_member_add(clipper, obj);
   cso->clipper = clipper;
   evas_object_color_set(cso->clipper, 255, 255, 255, 255);
   evas_object_move(cso->clipper, -100000, -100000);
   evas_object_resize(cso->clipper, 200000, 200000);
   evas_object_pass_events_set(cso->clipper, 1);
   evas_object_hide(cso->clipper);

   evas_object_smart_data_set(obj, cso);
}
