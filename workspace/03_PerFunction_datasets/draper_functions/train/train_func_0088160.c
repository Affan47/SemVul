evas_object_image_animated_frame_duration_get(const Evas_Object *obj, int start_frame, int frame_num)
{
   Evas_Object_Image *o;
   int frame_count = 0;

   if (start_frame < 1) return -1;
   if (frame_num < 0) return -1;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return -1;
   MAGIC_CHECK_END();
   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return -1;
   MAGIC_CHECK_END();

   if (!evas_object_image_animated_get(obj)) return -1;

   if (!obj->layer->evas->engine.func->image_animated_frame_count_get) return -1;

   frame_count = obj->layer->evas->engine.func->image_animated_frame_count_get(obj->layer->evas->engine.data.output, o->engine_data);

   if ((start_frame + frame_num) > frame_count) return -1;
   if (obj->layer->evas->engine.func->image_animated_frame_duration_get)
     return obj->layer->evas->engine.func->image_animated_frame_duration_get(obj->layer->evas->engine.data.output, o->engine_data, start_frame, frame_num);
   return -1;
}
