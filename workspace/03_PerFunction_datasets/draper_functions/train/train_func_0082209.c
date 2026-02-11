find_crypttab_entries_for_device (UDisksLinuxBlock *block,
                                  UDisksDaemon     *daemon)
{
  GList *entries;
  GList *l;
  GList *ret;

  ret = NULL;


  entries = udisks_crypttab_monitor_get_entries (udisks_daemon_get_crypttab_monitor (daemon));
  for (l = entries; l != NULL; l = l->next)
    {
      UDisksCrypttabEntry *entry = UDISKS_CRYPTTAB_ENTRY (l->data);
      const gchar *const *symlinks;
      const gchar *device_in_entry;
      const gchar *device = NULL;
      const gchar *label = NULL;
      const gchar *uuid = NULL;
      guint n;

      device_in_entry = udisks_crypttab_entry_get_device (entry);
      if (g_str_has_prefix (device_in_entry, "UUID="))
        {
          uuid = device_in_entry + 5;
        }
      else if (g_str_has_prefix (device_in_entry, "LABEL="))
        {
          label = device_in_entry + 6;
        }
      else if (g_str_has_prefix (device_in_entry, "/dev"))
        {
          device = device_in_entry;
        }
      else
        {

          goto continue_loop;
        }

      if (device != NULL)
        {
          if (g_strcmp0 (device, udisks_block_get_device (UDISKS_BLOCK (block))) == 0)
            {
              ret = g_list_prepend (ret, g_object_ref (entry));
            }
          else
            {
              symlinks = udisks_block_get_symlinks (UDISKS_BLOCK (block));
              if (symlinks != NULL)
                {
                  for (n = 0; symlinks[n] != NULL; n++)
                    {
                      if (g_strcmp0 (device, symlinks[n]) == 0)
                        {
                          ret = g_list_prepend (ret, g_object_ref (entry));
                        }
                    }
                }
            }
        }
      else if (label != NULL && g_strcmp0 (label, udisks_block_get_id_label (UDISKS_BLOCK (block))) == 0)
        {
          ret = g_list_prepend (ret, g_object_ref (entry));
        }
      else if (uuid != NULL && g_strcmp0 (uuid, udisks_block_get_id_uuid (UDISKS_BLOCK (block))) == 0)
        {
          ret = g_list_prepend (ret, g_object_ref (entry));
        }

    continue_loop:
      ;
    }

  g_list_foreach (entries, (GFunc) g_object_unref, NULL);
  g_list_free (entries);
  return ret;
}
