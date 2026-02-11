interpolate_none_get (GstTimedValueControlSource * self, GstClockTime timestamp,
    gdouble * value)
{
  gboolean ret = FALSE;
  GSequenceIter *iter;

  g_mutex_lock (&self->lock);

  iter =
      gst_timed_value_control_source_find_control_point_iter (self, timestamp);
  if (iter) {
    *value = _interpolate_none (self, iter);
    ret = TRUE;
  }
  g_mutex_unlock (&self->lock);
  return ret;
}
