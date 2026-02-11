gst_mpegts_descriptor_parse_dvb_service (const GstMpegTsDescriptor *
    descriptor, GstMpegTsDVBServiceType * service_type, gchar ** service_name,
    gchar ** provider_name)
{
  guint8 *data;

  g_return_val_if_fail (descriptor != NULL && descriptor->data != NULL, FALSE);
  g_return_val_if_fail (descriptor->tag == 0x48, FALSE);

  data = (guint8 *) descriptor->data + 2;

  if (service_type)
    *service_type = *data;
  data += 1;
  if (provider_name)
    *provider_name = get_encoding_and_convert ((const gchar *) data + 1, *data);
  data += *data + 1;
  if (service_name)
    *service_name = get_encoding_and_convert ((const gchar *) data + 1, *data);

  return TRUE;
}
