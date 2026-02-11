plugin_init (GstPlugin * plugin)
{
  gst_dp_init ();

  if (!gst_gdp_depay_plugin_init (plugin))
    return FALSE;

  if (!gst_gdp_pay_plugin_init (plugin))
    return FALSE;

  return TRUE;
}
