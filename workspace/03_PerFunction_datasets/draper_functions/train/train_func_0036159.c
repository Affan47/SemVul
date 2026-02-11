clutter_binding_pool_activate (ClutterBindingPool  *pool,
                               guint                key_val,
                               ClutterModifierType  modifiers,
                               GObject             *gobject)
{
  ClutterBindingEntry *entry = NULL;

  g_return_val_if_fail (pool != NULL, FALSE);
  g_return_val_if_fail (key_val != 0, FALSE);
  g_return_val_if_fail (G_IS_OBJECT (gobject), FALSE);

  modifiers = (modifiers & BINDING_MOD_MASK);

  entry = binding_pool_lookup_entry (pool, key_val, modifiers);
  if (!entry)
    return FALSE;

  if (!entry->is_blocked)
    return clutter_binding_entry_invoke (entry, gobject);

  return FALSE;
}
