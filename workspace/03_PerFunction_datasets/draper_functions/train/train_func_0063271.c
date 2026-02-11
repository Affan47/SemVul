rtp_source_set_sdes_struct (RTPSource * src, GstStructure * sdes)
{
  gboolean changed;

  g_return_val_if_fail (RTP_IS_SOURCE (src), FALSE);
  g_return_val_if_fail (strcmp (gst_structure_get_name (sdes),
          "application/x-rtp-source-sdes") == 0, FALSE);

  changed = !gst_structure_foreach (sdes, sdes_struct_compare_func, src->sdes);

  if (changed) {
    gst_structure_free (src->sdes);
    src->sdes = sdes;
  } else {
    gst_structure_free (sdes);
  }

  return changed;
}
