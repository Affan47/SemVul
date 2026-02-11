ensure_unused_cb (UDisksClient  *client,
                  GAsyncResult  *res,
                  gpointer       user_data)
{
  FormatVolumeData *data = user_data;
  GVariantBuilder options_builder;
  const gchar *erase_type;
  const gchar *fstype;
  const gchar *name;
  const gchar *passphrase;

  if (!gdu_utils_ensure_unused_finish (client, res, NULL))
    {
      format_volume_data_free (data);
      goto out;
    }

  erase_type = gdu_create_filesystem_widget_get_erase (GDU_CREATE_FILESYSTEM_WIDGET (data->create_filesystem_widget));
  fstype = gdu_create_filesystem_widget_get_fstype (GDU_CREATE_FILESYSTEM_WIDGET (data->create_filesystem_widget));
  name = gdu_create_filesystem_widget_get_name (GDU_CREATE_FILESYSTEM_WIDGET (data->create_filesystem_widget));
  passphrase = gdu_create_filesystem_widget_get_passphrase (GDU_CREATE_FILESYSTEM_WIDGET (data->create_filesystem_widget));

  g_variant_builder_init (&options_builder, G_VARIANT_TYPE_VARDICT);
  if (name != NULL && strlen (name) > 0)
    g_variant_builder_add (&options_builder, "{sv}", "label", g_variant_new_string (name));
  if (!(g_strcmp0 (fstype, "vfat") == 0 || g_strcmp0 (fstype, "ntfs") == 0))
    {

      g_variant_builder_add (&options_builder, "{sv}", "take-ownership", g_variant_new_boolean (TRUE));
    }
  if (passphrase != NULL && strlen (passphrase) > 0)
    g_variant_builder_add (&options_builder, "{sv}", "encrypt.passphrase", g_variant_new_string (passphrase));

  if (erase_type != NULL)
    g_variant_builder_add (&options_builder, "{sv}", "erase", g_variant_new_string (erase_type));

  g_variant_builder_add (&options_builder, "{sv}", "update-partition-type", g_variant_new_boolean (TRUE));

  udisks_block_call_format (data->block,
                            fstype,
                            g_variant_builder_end (&options_builder),
                            NULL,
                            format_cb,
                            data);

 out:
  ;
}
