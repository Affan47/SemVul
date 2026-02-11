elm_smart_scroller_child_set(Evas_Object *obj, Evas_Object *child)
{
   Evas_Coord w, h;
   Evas_Object *o;

   API_ENTRY return;
   if (sd->child_obj)
     {
        _elm_smart_pan_child_set(sd->pan_obj, NULL);
        evas_object_event_callback_del_full(sd->child_obj, EVAS_CALLBACK_DEL, _smart_child_del_hook, sd);
     }

   sd->child_obj = child;
   sd->wx = sd->wy = 0;

   sd->ww = sd->wh = -1;
   if (!child) return;

   if (!sd->pan_obj)
     {
        o = _elm_smart_pan_add(evas_object_evas_get(obj));
        sd->pan_obj = o;
        evas_object_smart_callback_add(o, "changed", _smart_pan_changed_hook, sd);
        edje_object_part_swallow(sd->edje_obj, "elm.swallow.content", o);
     }

   sd->pan_func.set = _elm_smart_pan_set;
   sd->pan_func.get = _elm_smart_pan_get;
   sd->pan_func.max_get = _elm_smart_pan_max_get;
   sd->pan_func.min_get = _elm_smart_pan_min_get;
   sd->pan_func.child_size_get = _elm_smart_pan_child_size_get;
   sd->pan_func.gravity_set = _elm_smart_pan_gravity_set;
   sd->pan_func.gravity_get = _elm_smart_pan_gravity_get;

   evas_object_event_callback_add(child, EVAS_CALLBACK_DEL, _smart_child_del_hook, sd);
   _elm_smart_pan_child_set(sd->pan_obj, child);
   sd->pan_func.child_size_get(sd->pan_obj, &w, &h);
   sd->child.w = w;
   sd->child.h = h;
   _smart_scrollbar_size_adjust(sd);
   _smart_scrollbar_reset(sd);
}
