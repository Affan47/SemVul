gst_mpegts_descriptor_parse_dvb_network_name (const GstMpegTsDescriptor *
    descriptor, gchar ** name)
{
  g_return_val_if_fail (descriptor != NULL && descriptor->data != NULL, FALSE);
  g_return_val_if_fail (descriptor->tag == 0x40, FALSE);

  *name = get_encoding_and_convert ((gchar *) descriptor->data + 2,
      descriptor->data[1]);
  return TRUE;
}
