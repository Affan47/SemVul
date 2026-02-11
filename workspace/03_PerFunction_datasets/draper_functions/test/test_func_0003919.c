clutter_binding_pool_get_for_class (gpointer klass)
{
  ClutterBindingPool *pool;

  g_return_val_if_fail (G_IS_OBJECT_CLASS (klass), NULL);

  if (G_UNLIKELY (key_class_bindings == 0))
    key_class_bindings = g_quark_from_static_string ("clutter-bindings-set");

  pool = g_dataset_id_get_data (klass, key_class_bindings);
  if (pool)
    return pool;

  pool = clutter_binding_pool_new (G_OBJECT_CLASS_NAME (klass));
  g_dataset_id_set_data_full (klass, key_class_bindings,
                              pool,
                              g_object_unref);

  return pool;
}
