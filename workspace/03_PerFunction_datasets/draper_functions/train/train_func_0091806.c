stpui_option_menu_new(gboolean            menu_only,


		       ...)
{
  GtkWidget *menu;
  GtkWidget *menuitem;


  const gchar    *label;
  GtkSignalFunc   callback;
  gpointer        data;
  gpointer        user_data;
  GtkWidget     **widget_ptr;
  gboolean        active;

  va_list args;
  gint    i;
  gint    initial_index;

  menu = gtk_menu_new ();


  initial_index = 0;

  va_start (args, menu_only);
  label = va_arg (args, const gchar *);

  for (i = 0; label; i++)
    {
      callback   = va_arg (args, GtkSignalFunc);
      data       = va_arg (args, gpointer);
      user_data  = va_arg (args, gpointer);
      widget_ptr = va_arg (args, GtkWidget **);
      active     = va_arg (args, gboolean);

      if (strcmp (label, "---"))
	{
	  menuitem = gtk_menu_item_new_with_label (label);

	  g_signal_connect (G_OBJECT (menuitem), "activate",
			    callback,
			    data);

	  if (user_data)
	    gtk_object_set_user_data (GTK_OBJECT (menuitem), user_data);
	}
      else
	{
	  menuitem = gtk_menu_item_new ();

	  gtk_widget_set_sensitive (menuitem, FALSE);
	}

      gtk_menu_append (GTK_MENU (menu), menuitem);

      if (widget_ptr)
	*widget_ptr = menuitem;

      gtk_widget_show (menuitem);


      if (active)
	initial_index = i;

      label = va_arg (args, const gchar *);
    }
  va_end (args);

  if (! menu_only)
    {
      GtkWidget *optionmenu;

      optionmenu = gtk_option_menu_new ();
      gtk_option_menu_set_menu (GTK_OPTION_MENU (optionmenu), menu);


      gtk_option_menu_set_history (GTK_OPTION_MENU (optionmenu), initial_index);

      return optionmenu;
    }

  return menu;
}
