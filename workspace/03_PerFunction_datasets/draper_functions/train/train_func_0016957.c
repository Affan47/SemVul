cd_profile_array_get_by_kind (CdProfileArray *profile_array,
			      CdProfileKind kind)
{
	CdProfileArrayPrivate *priv = profile_array->priv;
	CdProfile *profile_tmp;
	GPtrArray *array;
	guint i;


	array = g_ptr_array_new_with_free_func ((GDestroyNotify) g_object_unref);
	for (i = 0; i < priv->array->len; i++) {
		profile_tmp = g_ptr_array_index (priv->array, i);
		if (cd_profile_get_kind (profile_tmp) == kind) {
			g_ptr_array_add (array,
					 g_object_ref (profile_tmp));
		}
	}
	return array;
}
