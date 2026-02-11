gst_buffer_pool_config_add_option (GstStructure * config, const gchar * option)
{
  const GValue *value;
  GValue option_value = { 0, };
  guint i, len;

  g_return_if_fail (config != NULL);

  value = gst_structure_id_get_value (config, GST_QUARK (OPTIONS));
  if (value) {
    len = gst_value_array_get_size (value);
    for (i = 0; i < len; ++i) {
      const GValue *nth_val = gst_value_array_get_value (value, i);

      if (g_str_equal (option, g_value_get_string (nth_val)))
        return;
    }
  } else {
    GValue new_array_val = { 0, };

    g_value_init (&new_array_val, GST_TYPE_ARRAY);
    gst_structure_id_take_value (config, GST_QUARK (OPTIONS), &new_array_val);
    value = gst_structure_id_get_value (config, GST_QUARK (OPTIONS));
  }
  g_value_init (&option_value, G_TYPE_STRING);
  g_value_set_string (&option_value, option);
  gst_value_array_append_and_take_value ((GValue *) value, &option_value);
}
