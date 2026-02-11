evas_event_thaw_eval(Evas *e)
{
   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return;
   MAGIC_CHECK_END();
   if (e->events_frozen != 0) return;

   evas_event_feed_mouse_move(e, e->pointer.x, e->pointer.y,
                              e->last_timestamp, NULL);
}
