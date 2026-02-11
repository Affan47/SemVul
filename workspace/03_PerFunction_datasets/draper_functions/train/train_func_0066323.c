_new_local_candidate (
    FsStreamTransmitter *stream_transmitter,
    FsCandidate *candidate,
    gpointer user_data)
{
  FsRtpStream *self = FS_RTP_STREAM (user_data);
  FsRtpSession *session = fs_rtp_stream_get_session (self, NULL);
  GstElement *conf = NULL;

  if (!session)
    return;

  g_object_get (session, "conference", &conf, NULL);

  gst_element_post_message (conf,
      gst_message_new_element (GST_OBJECT (conf),
          gst_structure_new ("farstream-new-local-candidate",
              "stream", FS_TYPE_STREAM, self,
              "candidate", FS_TYPE_CANDIDATE, candidate,
              NULL)));

  gst_object_unref (conf);
  g_object_unref (session);
}
