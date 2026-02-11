ic_down_cb(void *data, Evas *e __UNUSED__, Evas_Object *obj, void *event_info)
{
   Evas_Event_Mouse_Down *ev = event_info;
   Ecore_Timer *tim;
   Evas_Coord x, y, w, h;

   evas_object_color_set(data, 128, 0, 0, 128);

   tim = evas_object_data_get(obj, "timer");
   if (tim) evas_object_data_del(obj, "timer");
   tim = ecore_timer_add(1.0, tim_cb, obj);
   evas_object_data_set(obj, "timer", tim);

   evas_object_geometry_get(data, &x, &y, &w, &h);
   evas_object_data_set(obj, "x", (void *)(uintptr_t)(ev->canvas.x));
   evas_object_data_set(obj, "y", (void *)(uintptr_t)(ev->canvas.y));
   evas_object_data_set(obj, "px", (void *)(uintptr_t)(x));
   evas_object_data_set(obj, "py", (void *)(uintptr_t)(y));

   if (ev->flags & EVAS_BUTTON_DOUBLE_CLICK)
     {
        printf("double click %p\n", obj);
     }
}
