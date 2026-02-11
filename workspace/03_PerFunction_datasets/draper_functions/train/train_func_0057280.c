main (int argc, char **argv)
{
  MxApplication *application;
  MxWindow *window;
  ClutterActor *box;
  MxToolbar *toolbar;
  gchar *selected_widget;

  application = mx_application_new (&argc, &argv, "test-widgets", 0);

  window = mx_application_create_window (application);

  if (argc > 1)
    selected_widget = argv[1];


  data.table = mx_table_new ();
  data.scroll = mx_scroll_view_new ();
  data.frame = mx_frame_new ();
  mx_bin_set_fill (MX_BIN (data.frame), TRUE, TRUE);
  data.container = NULL;
  data.inspector = NULL;
  data.child_inspector = NULL;

  mx_table_add_actor_with_properties (MX_TABLE (data.table), data.frame, 0, 0,
                                      "row-span", 2, NULL);
  mx_table_add_actor_with_properties (MX_TABLE (data.table), data.scroll, 0, 0,
                                      "row-span", 2, NULL);
  clutter_actor_set_height (data.scroll, 300);

  mx_window_set_child (window, data.table);


  box = mx_box_layout_new ();
  mx_box_layout_add_actor_with_properties (MX_BOX_LAYOUT (box),
                                           create_combo_box (selected_widget),
                                           0,
                                           "expand", TRUE,
                                           "x-fill", FALSE,
                                           "x-align", MX_ALIGN_START,
                                           NULL);
  mx_box_layout_add_actor (MX_BOX_LAYOUT (box), create_rotate_box (window), 1);

  toolbar = mx_window_get_toolbar (window);
  mx_bin_set_child (MX_BIN (toolbar), box);
  mx_bin_set_fill (MX_BIN (toolbar), TRUE, TRUE);


  mx_window_show (window);


  mx_application_run (application);

  return 0;
}
