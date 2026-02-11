evas_object_image_alpha_mask_set(Evas_Object *obj, Eina_Bool ismask)
{
   Evas_Object_Image *o;

   if (!ismask) return;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return;
   MAGIC_CHECK_END();


}
