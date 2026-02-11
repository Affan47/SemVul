_secret_session_encode_secret (SecretSession *session,
                               SecretValue *value)
{
	GVariantBuilder *builder;
	GVariant *result = NULL;
	GVariantType *type;
	gboolean ret;

	g_return_val_if_fail (session != NULL, NULL);
	g_return_val_if_fail (value != NULL, NULL);

	type = g_variant_type_new ("(oayays)");
	builder = g_variant_builder_new (type);

#ifdef WITH_GCRYPT
	if (session->key)
		ret = service_encode_aes_secret (session, value, builder);
	else
#endif
		ret = service_encode_plain_secret (session, value, builder);
	if (ret)
		result = g_variant_builder_end (builder);

	g_variant_builder_unref (builder);
	g_variant_type_free (type);
	return result;
}
