_ecore_evas_object_associate(Ecore_Evas *ee, Evas_Object *obj, Ecore_Evas_Object_Associate_Flags flags)
{
   evas_object_event_callback_add
     (obj, EVAS_CALLBACK_SHOW,
      _ecore_evas_obj_callback_show, ee);
   evas_object_event_callback_add
     (obj, EVAS_CALLBACK_HIDE,
      _ecore_evas_obj_callback_hide, ee);
   evas_object_event_callback_add
     (obj, EVAS_CALLBACK_RESIZE,
      _ecore_evas_obj_callback_resize, ee);
   evas_object_event_callback_add
     (obj, EVAS_CALLBACK_CHANGED_SIZE_HINTS,
      _ecore_evas_obj_callback_changed_size_hints, ee);
   if (flags & ECORE_EVAS_OBJECT_ASSOCIATE_DEL)
     evas_object_event_callback_add
       (obj, EVAS_CALLBACK_DEL, _ecore_evas_obj_callback_del, ee);
   else
     evas_object_event_callback_add
       (obj, EVAS_CALLBACK_DEL, _ecore_evas_obj_callback_del_dissociate, ee);

   evas_object_intercept_move_callback_add
     (obj, _ecore_evas_obj_intercept_move, ee);

   if (flags & ECORE_EVAS_OBJECT_ASSOCIATE_STACK)
     {
        evas_object_intercept_raise_callback_add
          (obj, _ecore_evas_obj_intercept_raise, ee);
        evas_object_intercept_lower_callback_add
          (obj, _ecore_evas_obj_intercept_lower, ee);
        evas_object_intercept_stack_above_callback_add
          (obj, _ecore_evas_obj_intercept_stack_above, ee);
        evas_object_intercept_stack_below_callback_add
          (obj, _ecore_evas_obj_intercept_stack_below, ee);
     }

   if (flags & ECORE_EVAS_OBJECT_ASSOCIATE_LAYER)
     evas_object_intercept_layer_set_callback_add
       (obj, _ecore_evas_obj_intercept_layer_set, ee);

   if (flags & ECORE_EVAS_OBJECT_ASSOCIATE_DEL)
     {
        ecore_evas_callback_delete_request_set(ee, _ecore_evas_delete_request);
        ecore_evas_callback_destroy_set(ee, _ecore_evas_destroy);
     }
   ecore_evas_callback_pre_free_set(ee, _ecore_evas_pre_free);
   ecore_evas_callback_resize_set(ee, _ecore_evas_resize);

   _evas_object_associate_set(obj, ee);
   _ecore_evas_associate_set(ee, obj);
}
