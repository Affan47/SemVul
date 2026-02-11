vorbis_streamheader_to_codecdata (const GValue * streamheader,
    GstMatroskaTrackContext * context)
{
  GstBuffer *buf0 = NULL;

  if (!xiphN_streamheader_to_codecdata (streamheader, context, &buf0, 3))
    return FALSE;

  if (buf0 == NULL || GST_BUFFER_SIZE (buf0) < 1 + 6 + 4) {
    GST_WARNING ("First vorbis header too small, ignoring");
  } else {
    if (memcmp (GST_BUFFER_DATA (buf0) + 1, "vorbis", 6) == 0) {
      GstMatroskaTrackAudioContext *audiocontext;
      guint8 *hdr;

      hdr = GST_BUFFER_DATA (buf0) + 1 + 6 + 4;
      audiocontext = (GstMatroskaTrackAudioContext *) context;
      audiocontext->channels = GST_READ_UINT8 (hdr);
      audiocontext->samplerate = GST_READ_UINT32_LE (hdr + 1);
    }
  }

  if (buf0)
    gst_buffer_unref (buf0);

  return TRUE;
}
