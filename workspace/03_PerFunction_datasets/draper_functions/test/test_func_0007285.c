on_ssrc_active (GObject * session, GObject * source, GstRTSPStream * stream)
{
  GST_DEBUG_OBJECT (stream->parent, "source in session %u is active",
      stream->id);
}
