caps_notify (GstPad * pad, GParamSpec * unused, GstRTSPMediaStream * stream)
{
  gchar *capsstr;
  GstCaps *newcaps, *oldcaps;

  if ((newcaps = GST_PAD_CAPS (pad)))
    gst_caps_ref (newcaps);

  oldcaps = stream->caps;
  stream->caps = newcaps;

  if (oldcaps)
    gst_caps_unref (oldcaps);

  capsstr = gst_caps_to_string (newcaps);
  GST_INFO ("stream %p received caps %p, %s", stream, newcaps, capsstr);
  g_free (capsstr);
}
