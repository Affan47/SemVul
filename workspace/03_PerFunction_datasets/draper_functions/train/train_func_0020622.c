udisks_crypttab_entry_compare (UDisksCrypttabEntry  *entry,
                               UDisksCrypttabEntry  *other_entry)
{
  gint ret;

  g_return_val_if_fail (UDISKS_IS_CRYPTTAB_ENTRY (entry), 0);
  g_return_val_if_fail (UDISKS_IS_CRYPTTAB_ENTRY (other_entry), 0);

  ret = g_strcmp0 (other_entry->name, entry->name);
  if (ret != 0)
    goto out;

  ret = g_strcmp0 (other_entry->device, entry->device);
  if (ret != 0)
    goto out;

  ret = g_strcmp0 (other_entry->passphrase_path, entry->passphrase_path);
  if (ret != 0)
    goto out;

  ret = g_strcmp0 (other_entry->options, entry->options);

 out:
  return ret;
}
