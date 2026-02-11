plugin_init (GstPlugin * plugin)
{
  if (!gst_element_register (plugin, "breakmydata", GST_RANK_NONE,
          gst_break_my_data_get_type ())
      || !gst_element_register (plugin, "capssetter", GST_RANK_NONE,
          gst_caps_setter_get_type ())
      || !gst_element_register (plugin, "rndbuffersize", GST_RANK_NONE,
          gst_rnd_buffer_size_get_type ())
      || !gst_element_register (plugin, "navseek", GST_RANK_NONE,
          gst_navseek_get_type ())
      || !gst_element_register (plugin, "pushfilesrc", GST_RANK_NONE,
          gst_push_file_src_get_type ()) ||

      !gst_element_register (plugin, "progressreport", GST_RANK_NONE,
          gst_progress_report_get_type ())
      || !gst_element_register (plugin, "taginject", GST_RANK_NONE,
          gst_tag_inject_get_type ())
      || !gst_element_register (plugin, "testsink", GST_RANK_NONE,
          gst_test_get_type ())
      || !gst_element_register (plugin, "capsdebug", GST_RANK_NONE,
          gst_caps_debug_get_type ())
      || !gst_element_register (plugin, "cpureport", GST_RANK_NONE,
          gst_cpu_report_get_type ()))

    return FALSE;

  return TRUE;
}
