buildDockMenu(VisuUiPanel *visu_ui_panel, GList *listOfDocks)
{
  GtkWidget *menu, *item;
  VisuUiDockWindow *window;
  gchar *lbl;

  menu = gtk_menu_new();


  while (listOfDocks)
    {
      window = (VisuUiDockWindow*)listOfDocks->data;
      if (window->show)
	{
	  lbl = g_strdup_printf(_("Send to '%s'"), window->name);
	  item = gtk_menu_item_new_with_label(lbl);
	  g_free(lbl);
	  g_signal_connect(G_OBJECT(item), "activate",
			   G_CALLBACK(onDockMenuClicked), listOfDocks->data);
	  g_object_set_qdata_full(G_OBJECT(item), CURRENT_TOOLPANEL_POINTER,
				  (gpointer)visu_ui_panel, NULL);
	  gtk_widget_set_sensitive(item, (visu_ui_panel->container != window));
	  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	}
      listOfDocks = g_list_next(listOfDocks);
    }

  item = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_menu_item_new_with_label(_("New dock"));
  g_signal_connect(G_OBJECT(item), "activate",
		   G_CALLBACK(onDockMenuNewClicked), (gpointer)visu_ui_panel);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  lbl = g_strdup_printf(_("Hide tool '%s'"), visu_ui_panel->tabLabel);
  item = gtk_menu_item_new_with_label(lbl);
  g_free(lbl);
  g_signal_connect(G_OBJECT(item), "activate",
		   G_CALLBACK(onDockMenuHideClicked), (gpointer)visu_ui_panel);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  DBG_fprintf(stderr, "Gtk VisuUiPanel : create the dock menu %p.\n", (gpointer)menu);

  return menu;
}
