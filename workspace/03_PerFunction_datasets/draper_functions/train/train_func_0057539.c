_transform_caps (GstUvcH264Src * self, GstCaps * caps, const gchar * name)
{
  GstElement *el = gst_element_factory_make (name, NULL);
  GstElement *cf = gst_element_factory_make ("capsfilter", NULL);
  GstElement *fs = gst_element_factory_make ("fakesink", NULL);
  GstPad *sink;
  GstCaps *out_caps = NULL;

  if (!el || !cf || !fs) {
    if (el)
      gst_object_unref (el);
    if (cf)
      gst_object_unref (cf);
    if (fs)
      gst_object_unref (fs);
    goto done;
  }

  gst_element_set_locked_state (el, TRUE);
  gst_element_set_locked_state (cf, TRUE);
  gst_element_set_locked_state (fs, TRUE);

  if (!gst_bin_add (GST_BIN (self), el)) {
    gst_object_unref (el);
    gst_object_unref (cf);
    gst_object_unref (fs);
    goto done;
  }
  if (!gst_bin_add (GST_BIN (self), cf)) {
    gst_object_unref (cf);
    gst_object_unref (fs);
    gst_bin_remove (GST_BIN (self), el);
    goto done;
  }
  if (!gst_bin_add (GST_BIN (self), fs)) {
    gst_object_unref (fs);
    gst_bin_remove (GST_BIN (self), el);
    gst_bin_remove (GST_BIN (self), cf);
    goto done;
  }

  g_object_set (cf, "caps", caps, NULL);

  if (!gst_element_link (cf, fs))
    goto error_remove;
  if (!gst_element_link (el, cf))
    goto error_remove;

  sink = gst_element_get_static_pad (el, "sink");
  if (!sink)
    goto error_remove;
  GST_DEBUG_OBJECT (self, "Transforming: %" GST_PTR_FORMAT, caps);

  caps = gst_pad_query_caps (sink, NULL);
  gst_object_unref (sink);

  GST_DEBUG_OBJECT (self, "Result: %" GST_PTR_FORMAT, out_caps);

error_remove:
  gst_bin_remove (GST_BIN (self), cf);
  gst_bin_remove (GST_BIN (self), el);
  gst_bin_remove (GST_BIN (self), fs);

done:
  if (out_caps == NULL)
    out_caps = gst_caps_copy (caps);

  return out_caps;
}
