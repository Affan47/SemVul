secret_password_storev (const SecretSchema *schema,
                        GHashTable *attributes,
                        const gchar *collection,
                        const gchar *label,
                        const gchar *password,
                        GCancellable *cancellable,
                        GAsyncReadyCallback callback,
                        gpointer user_data)
{
	SecretValue *value;

	g_return_if_fail (schema != NULL);
	g_return_if_fail (label != NULL);
	g_return_if_fail (password != NULL);
	g_return_if_fail (attributes != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));


	if (!_secret_attributes_validate (schema, attributes, G_STRFUNC, FALSE))
		return;

	value = secret_value_new (password, -1, "text/plain");

	secret_service_store (NULL, schema, attributes, collection,
	                      label, value, cancellable, callback, user_data);

	secret_value_unref (value);
}
