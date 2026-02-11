gst_mixer_mute_toggled (GstMixer * mixer, GstMixerTrack * track, gboolean mute)
{
  GstStructure *s;
  GstMessage *m;

  g_return_if_fail (mixer != NULL);
  g_return_if_fail (GST_IS_ELEMENT (mixer));
  g_return_if_fail (track != NULL);

  s = gst_structure_new (GST_MIXER_MESSAGE_NAME,
      "type", G_TYPE_STRING, "mute-toggled",
      "track", GST_TYPE_MIXER_TRACK, track, "mute", G_TYPE_BOOLEAN, mute, NULL);

  m = gst_message_new_element (GST_OBJECT (mixer), s);
  if (gst_element_post_message (GST_ELEMENT (mixer), m) == FALSE) {
    GST_WARNING ("This element has no bus, therefore no message sent!");
  }
}
