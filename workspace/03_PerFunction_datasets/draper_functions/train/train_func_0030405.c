_evas_object_image_cleanup(Evas_Object *obj, Evas_Object_Image *o)
{
   if ((o->preloading) && (o->engine_data))
     {
        o->preloading = 0;
        obj->layer->evas->engine.func->image_data_preload_cancel(obj->layer->evas->engine.data.output,
                                                                 o->engine_data,
                                                                 obj);
     }
   if (o->tmpf) _cleanup_tmpf(obj);
   if (o->cur.source) _proxy_unset(obj);
}
