_get_formatter (GstEncodeBin * ebin, GstEncodingProfile * sprof)
{
  GList *formatters, *tmpfmtr;
  GstElement *formatter = NULL;
  GstElementFactory *formatterfact = NULL;
  GstCaps *format;
  const gchar *preset, *preset_name;

  format = gst_encoding_profile_get_format (sprof);
  preset = gst_encoding_profile_get_preset (sprof);
  preset_name = gst_encoding_profile_get_preset_name (sprof);

  GST_DEBUG ("Getting list of formatters for format %" GST_PTR_FORMAT, format);

  formatters =
      gst_element_factory_list_filter (ebin->formatters, format, GST_PAD_SRC,
      FALSE);

  if (formatters == NULL)
    goto beach;


  for (tmpfmtr = formatters; tmpfmtr; tmpfmtr = tmpfmtr->next) {
    formatterfact = (GstElementFactory *) tmpfmtr->data;

    GST_DEBUG_OBJECT (ebin, "Trying formatter %s",
        GST_OBJECT_NAME (formatterfact));

    if ((formatter =
            _create_element_and_set_preset (formatterfact, preset,
                NULL, preset_name)))
      break;
  }

  gst_plugin_feature_list_free (formatters);

beach:
  if (format)
    gst_caps_unref (format);
  return formatter;
}
