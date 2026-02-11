block_has_jobs (GduDeviceTreeModel *model,
                UDisksBlock        *block)
{
  gboolean ret = FALSE;
  GDBusObject *block_object;
  UDisksPartitionTable *part_table = NULL;
  UDisksEncrypted *encrypted = NULL;
  GList *partitions = NULL, *l;
  UDisksBlock *cleartext_block = NULL;

  if (iface_has_jobs (model, G_DBUS_INTERFACE (block)))
    {
      ret = TRUE;
      goto out;
    }

  block_object = g_dbus_interface_get_object (G_DBUS_INTERFACE (block));
  if (block_object == NULL)
    goto out;

  part_table = udisks_object_get_partition_table (UDISKS_OBJECT (block_object));
  if (part_table != NULL)
    {
      partitions = udisks_client_get_partitions (model->client, part_table);
      for (l = partitions; l != NULL; l = l->next)
        {
          UDisksPartition *partition = UDISKS_PARTITION (l->data);
          GDBusObject *partition_object;
          UDisksBlock *partition_block;

          partition_object = g_dbus_interface_get_object (G_DBUS_INTERFACE (partition));
          if (partition_object != NULL)
            {
              partition_block = udisks_object_get_block (UDISKS_OBJECT (partition_object));
              if (block_has_jobs (model, partition_block))
                {
                  ret = TRUE;
                  goto out;
                }
            }
        }
    }

  encrypted = udisks_object_get_encrypted (UDISKS_OBJECT (block_object));
  if (encrypted != NULL)
    {
      cleartext_block = udisks_client_get_cleartext_block (model->client, block);
      if (cleartext_block != NULL)
        {
          if (block_has_jobs (model, cleartext_block))
            {
              ret = TRUE;
              goto out;
            }
        }
    }

 out:
  g_clear_object (&part_table);
  g_clear_object (&encrypted);
  g_clear_object (&cleartext_block);
  g_list_foreach (partitions, (GFunc) g_object_unref, NULL);
  g_list_free (partitions);
  return ret;
}
