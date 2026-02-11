_sub_table_remove(Evas_Object *obj,
                  Elm_Layout_Smart_Data *sd,
                  Elm_Layout_Sub_Object_Data *sub_d)
{
   Evas_Object *child;

   child = sub_d->obj;

   edje_object_part_table_unpack
     (ELM_WIDGET_DATA(sd)->resize_obj, sub_d->part, child);

   if (!elm_widget_sub_object_del(obj, child))
     {
        ERR("could not remove sub object %p from %p", child, obj);
        return NULL;
     }

   return child;
}
