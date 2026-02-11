plugin_init (GstPlugin * plugin)
{
  schro_init ();

  GST_DEBUG_CATEGORY_INIT (schro_debug, "schro", 0, "Schroedinger");
  gst_element_register (plugin, "schrodec", GST_RANK_PRIMARY,
      gst_schro_dec_get_type ());
  gst_element_register (plugin, "schroenc", GST_RANK_PRIMARY,
      gst_schro_enc_get_type ());

  return TRUE;
}
