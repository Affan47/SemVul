evas_object_pass_events_set(Evas_Object *obj, Eina_Bool pass)
{
   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   pass = !!pass;
   if (obj->pass_events == pass) return;
   obj->pass_events = pass;
   evas_object_smart_member_cache_invalidate(obj, EINA_TRUE, EINA_FALSE);
   if (evas_object_is_in_output_rect(obj,
                                     obj->layer->evas->pointer.x,
                                     obj->layer->evas->pointer.y, 1, 1) &&
       ((!obj->precise_is_inside) ||
        (evas_object_is_inside(obj,
                               obj->layer->evas->pointer.x,
                               obj->layer->evas->pointer.y))))
     evas_event_feed_mouse_move(obj->layer->evas,
                                obj->layer->evas->pointer.x,
                                obj->layer->evas->pointer.y,
                                obj->layer->evas->last_timestamp,
                                NULL);
}
