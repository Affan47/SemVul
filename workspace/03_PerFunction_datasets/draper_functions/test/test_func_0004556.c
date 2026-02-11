main (int argc, char **argv)
{
  GstElement *pipe, *filter;
  GstCaps *caps;
  gint width, height;
  gint xdir, ydir;
  gint round, type, stop;

  gst_init (&argc, &argv);

  type = 0;
  stop = -1;

  if (argc > 1) {
    type = atoi (argv[1]);
    stop = type + 1;
  }

  while (TRUE) {
    GstMessage *message;

    pipe = make_pipeline (type);
    if (pipe == NULL)
      break;

    filter = gst_bin_get_by_name (GST_BIN (pipe), "filter");
    g_assert (filter);

    width = 320;
    height = 240;
    xdir = ydir = -10;

    for (round = 0; round < MAX_ROUND; round++) {
      gchar *capsstr;
      g_print ("resize to %dx%d (%d/%d)   \r", width, height, round, MAX_ROUND);


      capsstr =
          g_strdup_printf ("video/x-raw, width=(int)%d, height=(int)%d;"
          "video/x-raw", width, height);

      caps = gst_caps_from_string (capsstr);
      g_free (capsstr);
      g_object_set (filter, "caps", caps, NULL);
      gst_caps_unref (caps);

      if (round == 0)
        gst_element_set_state (pipe, GST_STATE_PLAYING);

      width += xdir;
      if (width >= 320)
        xdir = -10;
      else if (width < 200)
        xdir = 10;

      height += ydir;
      if (height >= 240)
        ydir = -10;
      else if (height < 150)
        ydir = 10;

      message =
          gst_bus_poll (GST_ELEMENT_BUS (pipe), GST_MESSAGE_ERROR,
          50 * GST_MSECOND);
      if (message) {
        g_print ("got error           \n");

        gst_message_unref (message);
      }
    }
    g_print ("test %d done                    \n", type);

    gst_object_unref (filter);
    gst_element_set_state (pipe, GST_STATE_NULL);
    gst_object_unref (pipe);

    type++;
    if (type == stop)
      break;
  }
  return 0;
}
