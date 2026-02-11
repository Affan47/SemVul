evas_object_smart_free(Evas_Object *obj)
{
   Evas_Object_Smart *o;


   o = (Evas_Object_Smart *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Smart, MAGIC_OBJ_SMART);
   return;
   MAGIC_CHECK_END();

   o->magic = 0;
   EVAS_MEMPOOL_FREE(_mp_obj, o);
}
