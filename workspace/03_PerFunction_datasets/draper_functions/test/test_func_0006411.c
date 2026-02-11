gst_register_core_elements (GstPlugin * plugin)
{

  if (!gst_element_register (plugin, "bin", GST_RANK_PRIMARY,
          GST_TYPE_BIN) ||
      !gst_element_register (plugin, "pipeline", GST_RANK_PRIMARY,
          GST_TYPE_PIPELINE)
      )
    g_assert_not_reached ();

  return TRUE;
}
