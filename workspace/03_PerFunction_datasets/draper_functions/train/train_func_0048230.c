evas_layer_pre_free(Evas_Layer *lay)
{
   Evas_Object *obj;

   EINA_INLIST_FOREACH(lay->objects, obj)
     {
        if ((!obj->smart.parent) && (!obj->delete_me))
          evas_object_del(obj);
     }
}
