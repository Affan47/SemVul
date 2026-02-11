ibus_keyval_from_name (const gchar *keyval_name)
{
  gdk_key *found;

  g_return_val_if_fail (keyval_name != NULL, 0);

  found = bsearch (keyval_name, gdk_keys_by_name,
           IBUS_NUM_KEYS, sizeof (gdk_key),
           gdk_keys_name_compare);
  if (found != NULL)
    return found->keyval;
  else
    return IBUS_KEY_VoidSymbol;
}
