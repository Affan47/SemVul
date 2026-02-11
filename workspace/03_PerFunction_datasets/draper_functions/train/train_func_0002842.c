remove_timer(World *world, GSList *timeritem)
{
  Timer *timer = (Timer *) timeritem->data;

  we_timer_delete_timer(world, timer);

  world->timers = g_slist_remove_link(world->timers, timeritem);
  if (!timer->owner_plugin) {
    --world->timer_pos;
  }
  free_timer(timer, NULL);
  g_slist_free(timeritem);
}
