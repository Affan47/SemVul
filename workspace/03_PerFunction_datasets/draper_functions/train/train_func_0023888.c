notebook_page_notify_cb (GtkNotebook              *notebook,
			 GParamSpec               *spec,
                         GnomeControlCenterPrivate *priv)
{
  int nat_height;
  GtkWidget *child;

  child = notebook_get_selected_page (GTK_WIDGET (notebook));

  if (child == priv->scrolled_window || child == priv->search_scrolled)
    {
      gtk_widget_show (W (priv->builder, "search-entry"));
      gtk_widget_hide (W (priv->builder, "lock-button"));

      if (!g_strcmp0(g_getenv("XDG_CURRENT_DESKTOP"), "Unity"))
        gtk_widget_get_preferred_height_for_width (GTK_WIDGET (priv->main_vbox),
                                                   UNITY_FIXED_WIDTH, NULL, &nat_height);
      else
        gtk_widget_get_preferred_height_for_width (GTK_WIDGET (priv->main_vbox),
                                                   FIXED_WIDTH, NULL, &nat_height);
      gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (priv->scrolled_window),
                                                  priv->small_screen == SMALL_SCREEN_TRUE ? SMALL_SCREEN_FIXED_HEIGHT : nat_height);
    }
  else
    {
      gtk_widget_hide (W (priv->builder, "search-entry"));


      if (!g_strcmp0(g_getenv("XDG_CURRENT_DESKTOP"), "Unity")) {
        gtk_widget_get_preferred_height_for_width (GTK_WIDGET (priv->window),
                                                   UNITY_FIXED_WIDTH, NULL, &nat_height);
        gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (priv->scrolled_window), MIN_ICON_VIEW_HEIGHT);
        gtk_window_resize (GTK_WINDOW (priv->window),
                           UNITY_FIXED_WIDTH,
                           nat_height);
      }
      else {
        gtk_widget_get_preferred_height_for_width (GTK_WIDGET (priv->window),
                                                   FIXED_WIDTH, NULL, &nat_height);
        gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (priv->scrolled_window), MIN_ICON_VIEW_HEIGHT);
        gtk_window_resize (GTK_WINDOW (priv->window),
                           FIXED_WIDTH,
                           nat_height);
      }
    }
}
