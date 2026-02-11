_sub_obj_del(void        *data,
             Evas        *e __UNUSED__,
             Evas_Object *obj,
             void        *event_info __UNUSED__)
{
   Elm_Widget_Smart_Data *sd = data;

   if (_elm_widget_is(obj))
     {
        if (elm_widget_focus_get(obj)) _unfocus_parents(sd->obj);
     }
   if (obj == sd->resize_obj)
     {

        elm_widget_resize_object_set(sd->obj, NULL);
        return;
     }
   else if (obj == sd->hover_obj)
     {
        sd->hover_obj = NULL;
        return;
     }
   else if (_elm_legacy_is(sd->obj))
     {
        evas_object_smart_callback_call(sd->obj, "sub-object-del", obj);
        sd->subobjs = eina_list_remove(sd->subobjs, obj);
     }
   else
     {
        if (!elm_widget_sub_object_del(sd->obj, obj))
          ERR("failed to remove sub object %p from %p\n", obj, sd->obj);
     }
}
