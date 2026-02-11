gst_direct_control_binding_get_value (GstControlBinding * _self,
    GstClockTime timestamp)
{
  GstDirectControlBinding *self = GST_DIRECT_CONTROL_BINDING (_self);
  GValue *dst_val = NULL;
  gdouble src_val;

  g_return_val_if_fail (GST_IS_DIRECT_CONTROL_BINDING (self), NULL);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (timestamp), NULL);
  g_return_val_if_fail (GST_CONTROL_BINDING_PSPEC (self), FALSE);


  if (gst_control_source_get_value (self->cs, timestamp, &src_val)) {
    dst_val = g_new0 (GValue, 1);
    g_value_init (dst_val, G_PARAM_SPEC_VALUE_TYPE (_self->pspec));
    self->convert_g_value (self, src_val, dst_val);
  } else {
    GST_LOG ("no control value for property %s at ts %" GST_TIME_FORMAT,
        _self->name, GST_TIME_ARGS (timestamp));
  }

  return dst_val;
}
