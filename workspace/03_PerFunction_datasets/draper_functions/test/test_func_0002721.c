main (int argc, char **argv)
{
  GromitData *data;

  gtk_init (&argc, &argv);
  data = g_malloc (sizeof (GromitData));


  setup_client_app (data);


  gtk_selection_convert (data->win, GA_CONTROL, GA_STATUS,
                         GDK_CURRENT_TIME);
  gtk_main ();

  if (data->client)
    return main_client (argc, argv, data);


  setup_main_app (data, app_parse_args (argc, argv, data));
  gtk_main ();
  gdk_display_pointer_ungrab (data->display, GDK_CURRENT_TIME);
  gdk_cursor_unref (data->paint_cursor);
  gdk_cursor_unref (data->erase_cursor);
  g_free (data);
  return 0;
}
