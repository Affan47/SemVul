fill_type_dialog_set_values(struct fill_type_data *fill_type_data,
                                        OBJECT_FILLING type, gint width,
                                        gint pitch1, gint angle1,
                                        gint pitch2, gint angle2)
{
  gchar *text;
  GtkWidget *menu, *menuitem;

  if (type == -2)
    type = FILLING_VOID;
  gtk_option_menu_set_history(GTK_OPTION_MENU(fill_type_data->fill_type), type);
  menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(fill_type_data->fill_type));
  menuitem = gtk_menu_get_active(GTK_MENU(menu));
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), TRUE);

  if (width == -2)
    text = g_strdup(_("*unchanged*"));
  else
    text = g_strdup_printf ("%d", width);
  gtk_entry_set_text (GTK_ENTRY (fill_type_data->width_entry), text);
  gtk_entry_select_region (GTK_ENTRY (fill_type_data->width_entry),
                           0, strlen (text));
  g_free(text);

  if (pitch1 == -2)
    text = g_strdup(_("*unchanged*"));
  else
    text = g_strdup_printf ("%d", pitch1);
  gtk_entry_set_text (GTK_ENTRY (fill_type_data->pitch1_entry), text);
  gtk_entry_select_region (GTK_ENTRY (fill_type_data->pitch1_entry),
                           0, strlen (text));
  g_free(text);

  if (angle1 == -2)
    text = g_strdup(_("*unchanged*"));
  else
    text = g_strdup_printf ("%d", angle1);
  gtk_entry_set_text (GTK_ENTRY (fill_type_data->angle1_entry), text);
  gtk_entry_select_region (GTK_ENTRY (fill_type_data->angle1_entry),
                           0, strlen (text));
  g_free(text);

  if (pitch2 == -2)
    text = g_strdup(_("*unchanged*"));
  else
    text = g_strdup_printf ("%d", pitch2);
  gtk_entry_set_text (GTK_ENTRY (fill_type_data->pitch2_entry), text);
  gtk_entry_select_region (GTK_ENTRY (fill_type_data->pitch2_entry),
                           0, strlen (text));
  g_free(text);

  if (angle2 == -2)
    text = g_strdup(_("*unchanged*"));
  else
    text = g_strdup_printf ("%d", angle2);
  gtk_entry_set_text (GTK_ENTRY (fill_type_data->angle2_entry), text);
  gtk_entry_select_region (GTK_ENTRY (fill_type_data->angle2_entry),
                           0, strlen (text));
  g_free(text);
}
