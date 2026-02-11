editor_create_item_from_name (EggToolbarEditor *editor,
                              const char *      name,
                              GdkDragAction     drag_action)
{
  GtkWidget *item;
  const char *item_name;
  char *short_label;
  const char *collate_key;

  if (strcmp (name, "_separator") == 0)
    {
      GtkWidget *icon;

      icon = _egg_editable_toolbar_new_separator_image ();
      short_label = _("Separator");
      item_name = g_strdup (name);
      collate_key = g_utf8_collate_key (short_label, -1);
      item = editor_create_item (editor, GTK_IMAGE (icon),
                                 short_label, drag_action);
    }
  else
    {
      GtkAction *action;
      GtkWidget *icon;
      char *stock_id, *icon_name = NULL;

      action = find_action (editor, name);
      g_return_val_if_fail (action != NULL, NULL);

      g_object_get (action,
                    "icon-name", &icon_name,
                    "stock-id", &stock_id,
		    "short-label", &short_label,
		    NULL);


      if (icon_name)
        icon = gtk_image_new_from_icon_name (icon_name,
	                                     GTK_ICON_SIZE_LARGE_TOOLBAR);
      else
        icon = gtk_image_new_from_stock (stock_id ? stock_id : GTK_STOCK_DND,
                                         GTK_ICON_SIZE_LARGE_TOOLBAR);

      item_name = g_strdup (name);
      collate_key = g_utf8_collate_key (short_label, -1);
      item = editor_create_item (editor, GTK_IMAGE (icon),
                                 short_label, drag_action);

      g_free (short_label);
      g_free (stock_id);
      g_free (icon_name);
    }

  g_object_set_data_full (G_OBJECT (item), "egg-collate-key",
                          (gpointer) collate_key, g_free);
  g_object_set_data_full (G_OBJECT (item), "egg-item-name",
                          (gpointer) item_name, g_free);

  return item;
}
