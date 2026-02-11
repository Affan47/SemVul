evas_object_image_border_scale_get(const Evas_Object *obj)
{
   Evas_Object_Image *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return 1.0;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return 1.0;
   MAGIC_CHECK_END();
   return o->cur.border.scale;
}
