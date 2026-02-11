evas_object_image_load_scale_down_set(Evas_Object *obj, int scale_down)
{
   Evas_Object_Image *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return;
   MAGIC_CHECK_END();
   if (o->load_opts.scale_down_by == scale_down) return;
   o->load_opts.scale_down_by = scale_down;
   if (o->cur.file)
     {
	evas_object_image_unload(obj, 0);
        evas_object_inform_call_image_unloaded(obj);
	evas_object_image_load(obj);
	o->changed = 1;
	evas_object_change(obj);
     }
}
