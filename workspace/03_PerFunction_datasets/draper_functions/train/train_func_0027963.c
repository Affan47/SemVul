clutter_binding_pool_find_action (ClutterBindingPool  *pool,
                                  guint                key_val,
                                  ClutterModifierType  modifiers)
{
  ClutterBindingEntry *entry;

  g_return_val_if_fail (pool != NULL, NULL);
  g_return_val_if_fail (key_val != 0, NULL);

  entry = binding_pool_lookup_entry (pool, key_val, modifiers);
  if (!entry)
    return NULL;

  return entry->name;
}
