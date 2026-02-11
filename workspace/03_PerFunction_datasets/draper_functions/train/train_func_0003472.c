clutter_binding_pool_override_action (ClutterBindingPool  *pool,
                                      guint                key_val,
                                      ClutterModifierType  modifiers,
                                      GCallback            callback,
                                      gpointer             data,
                                      GDestroyNotify       notify)
{
  ClutterBindingEntry *entry;
  GClosure *closure;

  g_return_if_fail (pool != NULL);
  g_return_if_fail (key_val != 0);
  g_return_if_fail (callback != NULL);

  entry = binding_pool_lookup_entry (pool, key_val, modifiers);
  if (G_UNLIKELY (entry == NULL))
    {
      g_warning ("There is no action for the given key symbol "
                 "of %d (modifiers: %d) installed inside the "
                 "binding pool.",
                 key_val, modifiers);
      return;
    }

  if (entry->closure)
    {
      g_closure_unref (entry->closure);
      entry->closure = NULL;
    }

  closure = g_cclosure_new (callback, data, (GClosureNotify) notify);
  entry->closure = g_closure_ref (closure);
  g_closure_sink (closure);

  if (G_CLOSURE_NEEDS_MARSHAL (closure))
    {
      GClosureMarshal marshal;

      marshal = _clutter_marshal_BOOLEAN__STRING_UINT_FLAGS;
      g_closure_set_marshal (closure, marshal);
    }
}
