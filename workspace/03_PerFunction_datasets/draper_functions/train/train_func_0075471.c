log_manager_constructor (GType type,
    guint n_props,
    GObjectConstructParam *props)
{
  GObject *retval = NULL;

  if (G_LIKELY (manager_singleton))
    retval = g_object_ref (manager_singleton);
  else
    {
      retval = G_OBJECT_CLASS (tpl_log_manager_parent_class)->constructor (
          type, n_props, props);
      if (retval == NULL)
        return NULL;

      manager_singleton = TPL_LOG_MANAGER (retval);
      g_object_add_weak_pointer (retval, (gpointer *) &manager_singleton);
    }

  return retval;
}
