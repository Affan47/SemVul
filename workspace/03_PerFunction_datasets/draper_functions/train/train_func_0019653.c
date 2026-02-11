gst_object_get_value_arrays (GObject * object, GstClockTime timestamp,
    GSList * value_arrays)
{
  GstController *ctrl;

  g_return_val_if_fail (G_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (timestamp), FALSE);

  if ((ctrl = g_object_get_qdata (object, priv_gst_controller_key))) {
    return gst_controller_get_value_arrays (ctrl, timestamp, value_arrays);
  }
  return (FALSE);
}
