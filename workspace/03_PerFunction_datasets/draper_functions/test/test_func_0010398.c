gconf_settings_backend_write_one_to_changeset (const gchar    *key,
                                               GVariant       *value,
                                               GConfChangeSet *changeset)
{
  GConfValue *gconf_value;

  gconf_value = gconf_settings_backend_gvariant_to_gconf_value (value);
  if (gconf_value == NULL)
    return TRUE;

  gconf_change_set_set_nocopy (changeset, key, gconf_value);

  return FALSE;
}
