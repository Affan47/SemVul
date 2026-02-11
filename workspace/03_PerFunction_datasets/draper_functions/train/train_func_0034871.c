nemo_previewer_constructor (GType type,
                                guint n_construct_params,
                                GObjectConstructParam *construct_params)
{
  GObject *retval;

  if (singleton != NULL)
    return G_OBJECT (singleton);

  retval = G_OBJECT_CLASS (nemo_previewer_parent_class)->constructor
    (type, n_construct_params, construct_params);

  singleton = NEMO_PREVIEWER (retval);
  g_object_add_weak_pointer (retval, (gpointer) &singleton);

  return retval;
}
