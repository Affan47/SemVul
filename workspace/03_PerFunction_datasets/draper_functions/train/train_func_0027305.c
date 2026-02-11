evas_object_resize(Evas_Object *obj, Evas_Coord w, Evas_Coord h)
{
   int is, was = 0, pass = 0, freeze =0;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   if (obj->delete_me) return;
   if (w < 0) w = 0; if (h < 0) h = 0;

   if (evas_object_intercept_call_resize(obj, w, h)) return;

   if (obj->doing.in_resize > 0)
     {
        WRN("evas_object_resize() called on object %p when in the middle of resizing the same object", obj);
        return;
     }

   if ((obj->cur.geometry.w == w) && (obj->cur.geometry.h == h)) return;

   if (obj->layer->evas->events_frozen <= 0)
     {
        pass = evas_event_passes_through(obj);
        freeze = evas_event_freezes_through(obj);
        if ((!pass) && (!freeze))
          was = evas_object_is_in_output_rect(obj,
                                              obj->layer->evas->pointer.x,
                                              obj->layer->evas->pointer.y, 1, 1);
     }
   obj->doing.in_resize++;

   if (obj->smart.smart)
     {
       if (obj->smart.smart->smart_class->resize)
          obj->smart.smart->smart_class->resize(obj, w, h);
     }

   obj->cur.geometry.w = w;
   obj->cur.geometry.h = h;

   evas_object_update_bounding_box(obj);


   evas_object_change(obj);
   evas_object_clip_dirty(obj);
   obj->doing.in_resize--;

   if (obj->layer->evas->events_frozen <= 0)
     {

        evas_object_recalc_clippees(obj);


        if (!pass)
          {
             if (!obj->smart.smart)
               {
                  is = evas_object_is_in_output_rect(obj,
                                                     obj->layer->evas->pointer.x,
                                                     obj->layer->evas->pointer.y, 1, 1);
                  if ((is ^ was) && (obj->cur.visible))
                    evas_event_feed_mouse_move(obj->layer->evas,
                                               obj->layer->evas->pointer.x,
                                               obj->layer->evas->pointer.y,
                                               obj->layer->evas->last_timestamp,
                                               NULL);
               }
          }
     }
   evas_object_inform_call_resize(obj);
}
