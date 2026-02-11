gsd_locate_pointer_data_new (GdkScreen *screen)
{
  GsdLocatePointerData *data;

  data = g_new0 (GsdLocatePointerData, 1);


  data->widget = gtk_invisible_new ();
  gtk_widget_realize (data->widget);

  g_signal_connect (G_OBJECT (data->widget), "draw",
                    G_CALLBACK (locate_pointer_draw),
                    data);

  data->timeline = gsd_timeline_new (ANIMATION_LENGTH);
  g_signal_connect (data->timeline, "frame",
                    G_CALLBACK (timeline_frame_cb), data);
  g_signal_connect (data->timeline, "finished",
                    G_CALLBACK (timeline_finished_cb), data);

  create_window (data, screen);

  return data;
}
