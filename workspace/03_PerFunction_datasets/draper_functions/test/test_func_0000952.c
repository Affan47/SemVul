na_tray_manager_handle_dock_request (NaTrayManager       *manager,
				     XClientMessageEvent *xevent)
{
  Window icon_window = xevent->data.l[2];
  GtkWidget *child;

  if (g_hash_table_lookup (manager->socket_table,
                           GINT_TO_POINTER (icon_window)))
    {

      return;
    }

  child = na_tray_child_new (manager->screen, icon_window);
  if (child == NULL)
    return;

  g_signal_emit (manager, manager_signals[TRAY_ICON_ADDED], 0,
		 child);


  if (!GTK_IS_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (child))))
    {
      gtk_widget_destroy (child);
      return;
    }

  g_signal_connect (child, "plug_removed",
		    G_CALLBACK (na_tray_manager_plug_removed), manager);

  gtk_socket_add_id (GTK_SOCKET (child), icon_window);

  if (!gtk_socket_get_plug_window (GTK_SOCKET (child)))
    {


      g_signal_emit (manager, manager_signals[TRAY_ICON_REMOVED], 0, child);
      return;
    }

  g_hash_table_insert (manager->socket_table,
                       GINT_TO_POINTER (icon_window), child);
  gtk_widget_show (child);
}
