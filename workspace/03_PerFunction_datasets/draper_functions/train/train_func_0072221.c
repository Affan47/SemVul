meta_window_menu_popup (MetaWindowMenu     *menu,
                        int                 root_x,
                        int                 root_y,
                        int                 button,
                        guint32             timestamp)
{
  GdkPoint *pt;

  pt = g_new (GdkPoint, 1);

  g_object_set_data_full (G_OBJECT (menu->menu),
                          "destroy-point",
                          pt,
                          g_free);

  pt->x = root_x;
  pt->y = root_y;

  gtk_menu_popup (GTK_MENU (menu->menu),
                  NULL, NULL,
                  popup_position_func, pt,
                  button,
                  timestamp);

  if (!gtk_widget_get_visible (menu->menu))
    meta_warning ("GtkMenu failed to grab the pointer\n");
}
