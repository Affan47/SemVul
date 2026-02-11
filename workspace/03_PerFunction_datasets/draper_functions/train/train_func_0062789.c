gst_control_source_get_value (GstControlSource * self, GstClockTime timestamp,
    gdouble * value)
{
  g_return_val_if_fail (GST_IS_CONTROL_SOURCE (self), FALSE);

  if (G_LIKELY (self->get_value)) {
    return self->get_value (self, timestamp, value);
  } else {
    GST_ERROR ("Not bound to a specific property yet!");
    return FALSE;
  }
}
