main (int argc, char **argv)
{
  WnckScreen *screen;
  GtkWidget *sw;
  GtkWidget *win;
  GOptionContext *ctxt;

  ctxt = g_option_context_new ("");
  g_option_context_add_main_entries (ctxt, entries, NULL);
  g_option_context_add_group (ctxt, gtk_get_option_group (TRUE));
  g_option_context_parse (ctxt, &argc, &argv, NULL);
  g_clear_pointer (&ctxt, g_option_context_free);

  wnck_set_default_mini_icon_size (icon_size);

  gtk_init (&argc, &argv);

  screen = wnck_screen_get (0);

  g_signal_connect (G_OBJECT (screen), "active_window_changed",
                    G_CALLBACK (active_window_changed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "active_workspace_changed",
                    G_CALLBACK (active_workspace_changed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "window_stacking_changed",
                    G_CALLBACK (window_stacking_changed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "window_opened",
                    G_CALLBACK (window_opened_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "window_closed",
                    G_CALLBACK (window_closed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "workspace_created",
                    G_CALLBACK (workspace_created_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "workspace_destroyed",
                    G_CALLBACK (workspace_destroyed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "application_opened",
                    G_CALLBACK (application_opened_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "application_closed",
                    G_CALLBACK (application_closed_callback),
                    NULL);
  g_signal_connect (G_OBJECT (screen), "showing_desktop_changed",
                    G_CALLBACK (showing_desktop_changed_callback),
                    NULL);

  global_tree_model = create_tree_model ();
  global_tree_view = create_tree_view ();

  gtk_tree_view_set_model (GTK_TREE_VIEW (global_tree_view),
                           global_tree_model);

  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW (win), "Window List");

  sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);

  gtk_container_add (GTK_CONTAINER (sw), global_tree_view);
  gtk_container_add (GTK_CONTAINER (win), sw);

  gtk_window_set_default_size (GTK_WINDOW (win), 650, 550);


  g_signal_connect (G_OBJECT (win), "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  gtk_widget_show_all (win);

  gtk_main ();

  return 0;
}
