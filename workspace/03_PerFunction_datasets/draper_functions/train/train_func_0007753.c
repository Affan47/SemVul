jeex_menu_label_with_stock_append (GtkMenu * menu, const char *label,
                                   const char *stock_id, GCallback func,
                                   GtkAccelGroup * accel_group,
                                   unsigned int accel_id, GdkModifierType mod_type, char *tooltip)
{
  GtkWidget *widget, *image;

  image = gtk_image_new_from_stock (stock_id, GTK_ICON_SIZE_MENU);
  gtk_widget_show (image);

  widget = gtk_image_menu_item_new_with_label (label);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (widget), image);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), widget);
  gtk_widget_show (widget);

  if (func)
    g_signal_connect (G_OBJECT (widget), "activate", func, NULL);

  if (accel_id && accel_group)
    gtk_widget_add_accelerator (widget, "activate", accel_group, accel_id, mod_type, GTK_ACCEL_VISIBLE);

  if (tooltip)
    gtk_widget_set_tooltip_text (widget, tooltip);

  return widget;
}
