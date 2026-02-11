wait_for_luks_uuid (UDisksDaemon *daemon,
                    gpointer      user_data)
{
  FormatWaitData *data = user_data;
  UDisksObject *ret = NULL;
  UDisksBlock *block = NULL;

  block = udisks_object_get_block (data->object);
  if (block == NULL)
    goto out;

  if (g_strcmp0 (udisks_block_get_id_type (block), "crypto_LUKS") != 0)
    goto out;

  ret = g_object_ref (data->object);

 out:
  g_clear_object (&block);
  return ret;
}
