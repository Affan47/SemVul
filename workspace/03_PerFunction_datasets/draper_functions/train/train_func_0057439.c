gfs_event_init (GfsEvent * event,
		     GfsSimulation * sim)
{
  g_return_if_fail (event != NULL);
  g_return_if_fail (sim != NULL);

  if (event->start < 0.) {
    g_assert (GFS_EVENT_CLASS (GTS_OBJECT (event)->klass)->event);
    (* GFS_EVENT_CLASS (GTS_OBJECT (event)->klass)->event) (event, sim);
  }
  else if (event->end_event)
    event->t = event->start = G_MAXDOUBLE/2.;
  else {
    if (event->istep < G_MAXINT)
      while (event->i < sim->time.i) {
	event->n++;
	event->i += event->istep;
      }
    else
      while (event->t < sim->time.t) {
	event->n++;
	event->t = event->start + event->n*event->step;
      }
  }
}
