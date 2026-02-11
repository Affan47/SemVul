main (int argc, char *argv[])
{
  ClutterInitError error;
  ClutterColor     stage_color = { 0x00, 0x00, 0x00, 0x00 };
  ClutterActor    *stage = NULL;
  ClutterActor    *video = NULL;

  if (argc < 3)
    {
      g_print ("%s video1 video2\n", argv[0]);
      exit (1);
    }

  video_files[0] = argv[1];
  video_files[1] = argv[2];

  error = clutter_gst_init (&argc, &argv);
  g_assert (error == CLUTTER_INIT_SUCCESS);

  stage = clutter_stage_new ();
  clutter_actor_set_background_color (stage, &stage_color);

  video = clutter_gst_video_texture_new ();
  g_assert (CLUTTER_GST_IS_VIDEO_TEXTURE(video));

  g_signal_connect (CLUTTER_TEXTURE(video),
                    "size-change",
                    G_CALLBACK(size_change),
                    stage);
  g_signal_connect (CLUTTER_TEXTURE(video),
                    "error",
                    G_CALLBACK(on_error),
                    stage);
  g_timeout_add (5000, test, video);
  clutter_media_set_filename (CLUTTER_MEDIA(video), video_files[0]);
  clutter_media_set_audio_volume (CLUTTER_MEDIA(video), 0.5);
  clutter_media_set_playing (CLUTTER_MEDIA(video), TRUE);

  clutter_actor_add_child (stage, video);
  clutter_actor_show (stage);
  clutter_main ();

  return EXIT_SUCCESS;
}
