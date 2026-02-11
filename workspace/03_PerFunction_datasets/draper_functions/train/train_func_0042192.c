anjuta_recent_chooser_menu_create_item (AnjutaRecentChooserMenu *menu,
				     GtkRecentInfo        *info,
				     gint                  count)
{
  AnjutaRecentChooserMenuPrivate *priv;
  gchar *text;
  GtkWidget *item, *image, *label;
  GdkPixbuf *icon;

  g_assert (info != NULL);

  priv = menu->priv;

  if (priv->show_numbers)
    {
      gchar *name, *escaped;

      name = g_strdup (gtk_recent_info_get_display_name (info));
      if (!name)
        name = g_strdup (_("Unknown item"));

      escaped = escape_underscores (name);


      if (count <= 10)


        text = g_strdup_printf (C_("recent menu label", "_%d. %s"), count, escaped);
      else


        text = g_strdup_printf (C_("recent menu label", "%d. %s"), count, escaped);

      item = gtk_image_menu_item_new_with_mnemonic (text);

      g_free (escaped);
      g_free (name);
    }
  else
    {
      text = g_strdup (gtk_recent_info_get_display_name (info));
      item = gtk_image_menu_item_new_with_label (text);
    }

  g_free (text);


  label = gtk_bin_get_child (GTK_BIN (item));
  if (GTK_IS_LABEL (label))
    {
      gtk_label_set_ellipsize (GTK_LABEL (label), PANGO_ELLIPSIZE_END);
      gtk_label_set_max_width_chars (GTK_LABEL (label), priv->label_width);
    }

  if (priv->show_icons)
    {
      icon = gtk_recent_info_get_icon (info, priv->icon_size);

      image = gtk_image_new_from_pixbuf (icon);
      gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
      g_object_unref (icon);
    }

  g_signal_connect (item, "activate",
  		    G_CALLBACK (item_activate_cb),
  		    menu);

  return item;
}
