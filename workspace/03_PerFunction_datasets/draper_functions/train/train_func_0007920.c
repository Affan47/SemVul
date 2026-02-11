main (int argc, char **argv)
{
  GMainLoop *loop = NULL;
  GstElement *pipeline = NULL;
  GstBus *bus = NULL;
  GstElement *conf = NULL;
  FsParticipant *part = NULL;
  GError *error = NULL;
  GInputStream *istream = NULL;
  gchar *send_socket, *recv_socket;
  TestSession *ses;

  gst_init (&argc, &argv);

  if (argc != 3)
  {
    g_print ("Usage: %s <send socket> <recv_socket>\n", argv[0]);
    return 1;
  }

  send_socket = argv[1];
  recv_socket = argv[2];

  if (unlink (send_socket) < 0 && errno != ENOENT)
  {
    g_print ("Could not delete send or recv sockets");
    return 2;
  }

  g_print ("Press ENTER when the other side is ready\n");

  loop = g_main_loop_new (NULL, FALSE);

  pipeline = gst_pipeline_new (NULL);

  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, async_bus_cb, pipeline);
  gst_object_unref (bus);

  conf = gst_element_factory_make ("fsrtpconference", NULL);
  g_assert (conf);

  part = fs_conference_new_participant (FS_CONFERENCE (conf), &error);
  print_error (error);
  g_assert (part);

  g_assert (gst_bin_add (GST_BIN (pipeline), conf));

  istream = g_unix_input_stream_new (0, FALSE);

  ses = add_audio_session (pipeline, FS_CONFERENCE (conf), 1, part, send_socket,
      recv_socket);

  g_input_stream_skip_async (istream, 1, G_PRIORITY_DEFAULT, NULL, skipped_cb,
      ses);

  g_assert (gst_element_set_state (pipeline, GST_STATE_PLAYING) !=
      GST_STATE_CHANGE_FAILURE);
  g_main_loop_run (loop);

  g_assert (gst_element_set_state (pipeline, GST_STATE_NULL) !=
      GST_STATE_CHANGE_FAILURE);

  g_object_unref (part);
  g_object_unref (istream);

  free_session (ses);

  gst_object_unref (pipeline);
  g_main_loop_unref (loop);

  return 0;
}
