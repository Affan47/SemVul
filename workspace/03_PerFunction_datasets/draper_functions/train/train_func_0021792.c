gfs_event_next (GfsEvent * event, GfsSimulation * sim)
{
  g_return_val_if_fail (event != NULL, G_MAXDOUBLE);
  g_return_val_if_fail (sim != NULL, G_MAXDOUBLE);

  if (sim->time.t < event->t)
    return event->t;
  if (event->t >= event->end ||
      event->i >= event->iend ||
      sim->time.t > event->end ||
      sim->time.i > event->iend)
    return G_MAXDOUBLE;
  if (event->end_event)
    return G_MAXDOUBLE;
  if (sim->time.t >= event->t) {
    if (event->istep < G_MAXINT) {
      if (event->n == 0)
	return G_MAXDOUBLE;
    }
    else
      return event->start + (event->n + 1)*event->step;
  }
  if (sim->time.i >= event->i && event->step < G_MAXDOUBLE && event->n == 0)
    return sim->time.t + event->step;
  return G_MAXDOUBLE;
}
