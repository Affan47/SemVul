add_on_menu_item_activated (GtkMenuItem *item,
                            gpointer     user_data)
{
  DialogData *data = user_data;
  GList *objects = NULL;
  UDisksBlock *block;
  UDisksObject *object;
  GVariantBuilder options_builder;

  block = UDISKS_BLOCK (g_object_get_data (G_OBJECT (item), "x-udisks-block"));
  object = UDISKS_OBJECT (g_dbus_interface_dup_object (G_DBUS_INTERFACE (block)));

  objects = g_list_append (NULL, object);
  if (!gdu_utils_show_confirmation (GTK_WINDOW (data->dialog),
                                    C_("mdraid-disks", "Are you sure you want to add the disk to the array?"),
                                    C_("mdraid-disks", "All existing data on the disk will be lost"),
                                    C_("mdraid-disks", "_Add"),
                                    NULL, NULL,
                                    gdu_window_get_client (data->window), objects))
    goto out;

  g_variant_builder_init (&options_builder, G_VARIANT_TYPE_VARDICT);
  udisks_mdraid_call_add_device (data->mdraid,
                                 g_dbus_object_get_object_path (G_DBUS_OBJECT (object)),
                                 g_variant_builder_end (&options_builder),
                                 NULL,
                                 (GAsyncReadyCallback) add_device_cb,
                                 dialog_data_ref (data));

 out:
  g_clear_object (&object);
  g_list_free (objects);
}
