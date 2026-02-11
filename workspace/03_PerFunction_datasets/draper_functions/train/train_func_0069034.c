evas_object_image_add(Evas *e)
{
   Evas_Object *obj;
   Evas_Object_Image *o;

   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return NULL;
   MAGIC_CHECK_END();
   EINA_SAFETY_ON_NULL_RETURN_VAL(e->engine.func, NULL);
   obj = evas_object_new(e);
   evas_object_image_init(obj);
   evas_object_inject(obj, e);
   o = (Evas_Object_Image *)(obj->object_data);
   o->cur.cspace = obj->layer->evas->engine.func->image_colorspace_get(obj->layer->evas->engine.data.output,
								       o->engine_data);
   return obj;
}
