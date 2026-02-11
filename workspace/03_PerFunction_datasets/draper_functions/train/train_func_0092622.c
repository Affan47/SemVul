gck_object_cache_lookup (GckObject *object,
                         const gulong *attr_types,
                         gint n_attr_types,
                         GCancellable *cancellable,
                         GError **error)
{
	GckAttributes *attrs;
	GckObjectCache *cache;

	g_return_val_if_fail (GCK_IS_OBJECT (object), NULL);
	g_return_val_if_fail (attr_types != NULL || n_attr_types == 0, NULL);
	g_return_val_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	if (GCK_IS_OBJECT_CACHE (object)) {
		cache = GCK_OBJECT_CACHE (object);
		attrs = gck_object_cache_get_attributes (cache);
		if (check_have_attributes (attrs, attr_types, n_attr_types))
			return attrs;
		gck_attributes_unref (attrs);

		if (!gck_object_cache_update (cache, attr_types, n_attr_types,
		                              cancellable, error))
			return NULL;

		return gck_object_cache_get_attributes (cache);

	} else {
		return gck_object_get_full (object, attr_types, n_attr_types,
		                            cancellable, error);
	}
}
