evas_object_image_native_surface_set(Evas_Object *obj, Evas_Native_Surface *surf)
{
   Evas_Object_Image *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return;
   MAGIC_CHECK_END();
   _evas_object_image_cleanup(obj, o);
   if (!obj->layer->evas->engine.func->image_native_set) return;
   if ((surf) &&
       ((surf->version < 2) ||
        (surf->version > EVAS_NATIVE_SURFACE_VERSION))) return;
   o->engine_data =
      obj->layer->evas->engine.func->image_native_set(obj->layer->evas->engine.data.output,
                                                      o->engine_data,
                                                      surf);
}
