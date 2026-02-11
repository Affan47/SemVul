gst_encode_bin_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * name, const GstCaps * caps)
{
  GstEncodeBin *ebin = (GstEncodeBin *) element;
  GstPad *res = NULL;

  GST_DEBUG_OBJECT (element, "templ:%s, name:%s", templ->name_template, name);


  if (caps != NULL) {
    res = request_pad_for_stream (ebin, G_TYPE_NONE, name, (GstCaps *) caps);
  }

  if (res == NULL) {
    GType ptype = G_TYPE_NONE;

    if (!strcmp (templ->name_template, "video_%d"))
      ptype = GST_TYPE_ENCODING_VIDEO_PROFILE;
    else if (!strcmp (templ->name_template, "audio_%d"))
      ptype = GST_TYPE_ENCODING_AUDIO_PROFILE;


    res = request_pad_for_stream (ebin, ptype, name, NULL);
  }

  return res;
}
