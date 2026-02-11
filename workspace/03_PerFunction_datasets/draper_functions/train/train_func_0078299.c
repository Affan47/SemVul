e_zone_move_resize(E_Zone *zone,
                   int     x,
                   int     y,
                   int     w,
                   int     h)
{
   E_Event_Zone_Move_Resize *ev;

   E_OBJECT_CHECK(zone);
   E_OBJECT_TYPE_CHECK(zone, E_ZONE_TYPE);

   if ((x == zone->x) && (y == zone->y) && (w == zone->w) && (h == zone->h))
     return;

   zone->x = x;
   zone->y = y;
   zone->w = w;
   zone->h = h;

   evas_object_move(zone->bg_object, x, y);
   evas_object_move(zone->bg_event_object, x, y);
   evas_object_move(zone->bg_clip_object, x, y);
   evas_object_resize(zone->bg_object, w, h);
   evas_object_resize(zone->bg_event_object, w, h);
   evas_object_resize(zone->bg_clip_object, w, h);

   ev = E_NEW(E_Event_Zone_Move_Resize, 1);
   ev->zone = zone;
   e_object_ref(E_OBJECT(ev->zone));
   ecore_event_add(E_EVENT_ZONE_MOVE_RESIZE, ev,
                   _e_zone_event_move_resize_free, NULL);

   _e_zone_edge_move_resize(zone);

   e_zone_bg_reconfigure(zone);
   if (zone->black_need > 0)
     {
        ecore_evas_move(zone->black_ecore_evas, zone->x, zone->y);
        ecore_evas_resize(zone->black_ecore_evas, zone->w, zone->h);
     }
   _e_zone_border_geometry_update(zone);
}
