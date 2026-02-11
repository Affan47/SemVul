e_scrollframe_child_set(Evas_Object *obj, Evas_Object *child)
{
   Evas_Object *o;

   API_ENTRY return;
   if (sd->child_obj)
     {
        if (sd->pan_obj)
          {
             e_pan_child_set(sd->pan_obj, NULL);
             evas_object_event_callback_del(sd->child_obj, EVAS_CALLBACK_FREE,
                                            _e_smart_child_del_hook);
          }
     }

   sd->child_obj = child;
   if (!child) return;

   if (!sd->pan_obj)
     {
        o = e_pan_add(evas_object_evas_get(obj));
        sd->pan_obj = o;
        evas_object_smart_callback_add(o, "changed",
                                       _e_smart_pan_changed_hook, sd);
        evas_object_smart_callback_add(o, "pan_changed",
                                       _e_smart_pan_pan_changed_hook, sd);
        evas_object_show(o);
        edje_object_part_swallow(sd->edje_obj, "e.swallow.content", o);
     }

   sd->pan_func.set = e_pan_set;
   sd->pan_func.get = e_pan_get;
   sd->pan_func.max_get = e_pan_max_get;
   sd->pan_func.child_size_get = e_pan_child_size_get;

   evas_object_event_callback_add(child, EVAS_CALLBACK_FREE,
                                  _e_smart_child_del_hook, sd);
   e_pan_child_set(sd->pan_obj, sd->child_obj);
   sd->pan_func.child_size_get(sd->pan_obj, &sd->child.w, &sd->child.h);
   _e_smart_scrollbar_size_adjust(sd);
   _e_smart_scrollbar_reset(sd);
}
