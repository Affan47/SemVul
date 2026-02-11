evas_object_image_scale_hint_set(Evas_Object *obj, Evas_Image_Scale_Hint hint)
{
   Evas_Object_Image *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return;
   MAGIC_CHECK_END();
   if (o->scale_hint == hint) return;
   o->scale_hint = hint;
   if (o->engine_data)
     {
        int stride = 0;

        if (obj->layer->evas->engine.func->image_scale_hint_set)
           obj->layer->evas->engine.func->image_scale_hint_set
           (obj->layer->evas->engine.data.output,
               o->engine_data, o->scale_hint);
        if (obj->layer->evas->engine.func->image_stride_get)
           obj->layer->evas->engine.func->image_stride_get
           (obj->layer->evas->engine.data.output,
               o->engine_data, &stride);
        else
           stride = o->cur.image.w * 4;
        o->cur.image.stride = stride;
     }
}
