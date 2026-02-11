swfdec_gst_connect_sinkpad_by_pad (GstPad *srcpad, GstCaps *caps)
{
  GstPadTemplate *tmpl;
  GstPad *sinkpad;

  gst_caps_ref (caps);
  tmpl = gst_pad_template_new ("sink", GST_PAD_SINK, GST_PAD_ALWAYS, caps);
  sinkpad = gst_pad_new_from_template (tmpl, "sink");
  g_object_unref (tmpl);
  if (gst_pad_link (srcpad, sinkpad) != GST_PAD_LINK_OK)
    goto error;

  gst_pad_set_active (sinkpad, TRUE);
  return sinkpad;

error:
  SWFDEC_ERROR ("failed to create or link sinkpad");
  gst_object_unref (sinkpad);
  return NULL;
}
