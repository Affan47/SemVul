gkm_store_read_string (GkmStore *self, GkmObject *object, CK_ATTRIBUTE_TYPE type)
{
	gconstpointer value;
	gsize n_value;

	g_return_val_if_fail (GKM_IS_STORE (self), NULL);
	g_return_val_if_fail (GKM_IS_OBJECT (object), NULL);

	value = gkm_store_read_value (self, object, type, &n_value);
	if (!value)
		return NULL;

	return g_strndup (value, n_value);
}
