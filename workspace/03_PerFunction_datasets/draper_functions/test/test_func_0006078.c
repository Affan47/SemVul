_elm_notify_smart_sub_object_del(Evas_Object *obj,
                                 Evas_Object *sobj)
{
   ELM_NOTIFY_DATA_GET(obj, sd);

   if (!ELM_WIDGET_CLASS(_elm_notify_parent_sc)->sub_object_del(obj, sobj))
     return EINA_FALSE;

   if (sobj == sd->content)
     {
        evas_object_event_callback_del_full
          (sobj, EVAS_CALLBACK_CHANGED_SIZE_HINTS,
          _changed_size_hints_cb, obj);
        evas_object_event_callback_del_full
          (sobj, EVAS_CALLBACK_RESIZE, _content_resize_cb, obj);
        sd->content = NULL;
     }

   return EINA_TRUE;
}
