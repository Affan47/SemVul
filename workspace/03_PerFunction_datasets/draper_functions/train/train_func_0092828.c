evas_object_release(Evas_Object *obj, int clean_layer)
{
   if (!obj->in_layer) return;
   obj->layer->objects = (Evas_Object *)eina_inlist_remove(EINA_INLIST_GET(obj->layer->objects), EINA_INLIST_GET(obj));
   obj->layer->usage--;
   if (clean_layer)
     {
        if (obj->layer->usage <= 0)
          {
             evas_layer_del(obj->layer);
             _evas_layer_free(obj->layer);
          }
     }
   obj->layer = NULL;
   obj->in_layer = 0;
}
