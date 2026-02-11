gst_mpegts_descriptor_parse_iso_639_language (const GstMpegTsDescriptor *
    descriptor, GstMpegTsISO639LanguageDescriptor * res)
{
  guint i;
  guint8 *data;

  g_return_val_if_fail (descriptor != NULL && descriptor->data != NULL, FALSE);
  g_return_val_if_fail (res != NULL, FALSE);
  g_return_val_if_fail (descriptor->tag == 0x0A, FALSE);

  data = (guint8 *) descriptor->data + 2;

  res->nb_language = descriptor->length / 4;
  for (i = 0; i < res->nb_language; i++) {
    memcpy (res->language[i], data, 3);
    res->audio_type[i] = data[3];
    data += 4;
  }
  return TRUE;

}
