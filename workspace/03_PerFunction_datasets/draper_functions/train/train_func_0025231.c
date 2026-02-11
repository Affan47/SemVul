exo_die_editor_cell_data_func (GtkCellLayout   *cell_layout,
                               GtkCellRenderer *renderer,
                               GtkTreeModel    *model,
                               GtkTreeIter     *iter,
                               gpointer         user_data)
{
  ExoDieEditor *editor = EXO_DIE_EDITOR (user_data);
  GtkIconTheme *icon_theme;
  GdkPixbuf    *pixbuf_scaled;
  GdkPixbuf    *pixbuf = NULL;
  gchar        *icon;
  gint          pixbuf_width;
  gint          pixbuf_height;


  gtk_tree_model_get (model, iter, EXO_DIE_DESKTOP_MODEL_COLUMN_ICON, &icon, -1);


  if (icon != NULL && g_path_is_absolute (icon))
    {

      pixbuf = gdk_pixbuf_new_from_file (icon, NULL);
    }
  else if (!exo_str_is_empty (icon))
    {

      icon_theme = gtk_icon_theme_get_for_screen (gtk_widget_get_screen (GTK_WIDGET (editor)));


      pixbuf = gtk_icon_theme_load_icon (icon_theme, icon, 16, 0, NULL);
    }


  if (G_LIKELY (pixbuf != NULL))
    {

      pixbuf_width = gdk_pixbuf_get_width (pixbuf);
      pixbuf_height = gdk_pixbuf_get_height (pixbuf);
      if (G_UNLIKELY (pixbuf_width > 16 || pixbuf_height > 16))
        {
          pixbuf_scaled = exo_gdk_pixbuf_scale_ratio (pixbuf, 16);
          g_object_unref (G_OBJECT (pixbuf));
          pixbuf = pixbuf_scaled;
        }
    }


  g_object_set (G_OBJECT (renderer), "pixbuf", pixbuf, NULL);


  if (G_LIKELY (pixbuf != NULL))
    g_object_unref (G_OBJECT (pixbuf));
  g_free (icon);
}
