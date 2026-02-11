main (gint argc, gchar * argv[])
{
  GstStateChangeReturn res;
  GstElement *player;
  GMainLoop *loop;
  GstBus *bus;

  gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, TRUE);

  if (argc < 2) {
    g_print ("usage: %s <uri> [<uri> ... ]\n", argv[0]);
    exit (-1);
  }

  player = gst_element_factory_make ("playbin2", "player");
  g_assert (player);

  bus = gst_pipeline_get_bus (GST_PIPELINE (player));
  gst_bus_add_signal_watch (bus);

  g_signal_connect (bus, "message::eos", G_CALLBACK (eos_cb), loop);
  g_signal_connect (bus, "message::error", G_CALLBACK (error_cb), loop);
  g_signal_connect (bus, "message::warning", G_CALLBACK (warning_cb), NULL);
  g_signal_connect (bus, "message::new-clock", G_CALLBACK (new_clock_cb), NULL);
  g_signal_connect (bus, "message::clock-lost", G_CALLBACK (clock_lost_cb),
      player);

  g_object_set (G_OBJECT (player), "uri", argv[1], NULL);

  arg_count = 2;
  max_count = argc;
  g_signal_connect (player, "about-to-finish", G_CALLBACK (about_to_finish_cb),
      argv);

  res = gst_element_set_state (player, GST_STATE_PLAYING);
  if (res == GST_STATE_CHANGE_FAILURE) {
    g_print ("could not play\n");
    return -1;
  }

  g_timeout_add (UPDATE_INTERVAL, (GSourceFunc) update_scale, player);

  g_main_loop_run (loop);


  gst_element_set_state (player, GST_STATE_NULL);
  gst_object_unref (player);
  gst_object_unref (bus);

  return 0;
}
