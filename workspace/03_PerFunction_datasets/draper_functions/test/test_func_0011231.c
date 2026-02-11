gnac_properties_dup_channels(const GValue *value)
{
  guint val = g_value_get_uint(value);
  if (val == 0) return NULL;


  return g_strdup_printf("%d%s", val,
      val == 1 ? _(" (mono)") : val == 2 ? _(" (stereo)") : "");
}
