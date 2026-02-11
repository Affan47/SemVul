_down_cb(void *data,
         Evas *e __UNUSED__,
         Evas_Object *obj __UNUSED__,
         void *event_info)
{
   Evas_Event_Mouse_Down *ev = event_info;
   Evas_Object *fl = data;
   Evas_Coord x, y, w, h;

   ELM_FLIP_DATA_GET(fl, sd);

   if (ev->button != 1) return;
   if (ev->event_flags & EVAS_EVENT_FLAG_ON_HOLD) return;
   if (sd->animator)
     {
        ecore_animator_del(sd->animator);
        sd->animator = NULL;
     }
   sd->down = EINA_TRUE;
   sd->started = EINA_FALSE;
   evas_object_geometry_get(data, &x, &y, &w, &h);
   sd->x = ev->canvas.x - x;
   sd->y = ev->canvas.y - y;
   sd->w = w;
   sd->h = h;
   sd->down_x = sd->x;
   sd->down_y = sd->y;
}
