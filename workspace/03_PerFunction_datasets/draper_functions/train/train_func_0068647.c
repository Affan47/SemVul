clutter_layout_manager_find_child_property (ClutterLayoutManager *manager,
                                            const gchar          *name)
{
  ClutterLayoutManagerClass *klass;
  GObjectClass *meta_klass;
  GParamSpec *pspec;
  GType meta_type;

  klass = CLUTTER_LAYOUT_MANAGER_GET_CLASS (manager);
  meta_type = klass->get_child_meta_type (manager);
  if (meta_type == G_TYPE_INVALID)
    return NULL;

  meta_klass = g_type_class_ref (meta_type);

  pspec = g_object_class_find_property (meta_klass, name);

  g_type_class_unref (meta_klass);

  return pspec;
}
