gst_direct_control_binding_get_g_value_array (GstControlBinding * _self,
    GstClockTime timestamp, GstClockTime interval, guint n_values,
    GValue * values)
{
  GstDirectControlBinding *self = GST_DIRECT_CONTROL_BINDING (_self);
  gint i;
  gdouble *src_val;
  gboolean res = FALSE;
  GType type;
  GstDirectControlBindingConvertGValue convert;

  g_return_val_if_fail (GST_IS_DIRECT_CONTROL_BINDING (self), FALSE);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (timestamp), FALSE);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (interval), FALSE);
  g_return_val_if_fail (values, FALSE);
  g_return_val_if_fail (GST_CONTROL_BINDING_PSPEC (self), FALSE);

  convert = self->convert_g_value;
  type = G_PARAM_SPEC_VALUE_TYPE (_self->pspec);

  src_val = g_new0 (gdouble, n_values);
  if ((res = gst_control_source_get_value_array (self->cs, timestamp,
              interval, n_values, src_val))) {
    for (i = 0; i < n_values; i++) {

      if (!isnan (src_val[i])) {
        g_value_init (&values[i], type);
        convert (self, src_val[i], &values[i]);
      } else {
        GST_LOG ("no control value for property %s at index %d", _self->name,
            i);
      }
    }
  } else {
    GST_LOG ("failed to get control value for property %s at ts %"
        GST_TIME_FORMAT, _self->name, GST_TIME_ARGS (timestamp));
  }
  g_free (src_val);
  return res;
}
