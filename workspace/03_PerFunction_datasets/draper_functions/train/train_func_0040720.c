migrate_parse_smime (ParseData *parse_data,
                     const gchar *element_name,
                     const gchar **attribute_names,
                     const gchar **attribute_values,
                     GError **error)
{
	const gchar *hash_algo;
	gboolean encrypt_default;
	gboolean encrypt_to_self;
	gboolean sign_default;
	gboolean success;

	success = g_markup_collect_attributes (
		element_name,
		attribute_names,
		attribute_values,
		error,
		G_MARKUP_COLLECT_BOOLEAN,
		"encrypt-default", &encrypt_default,
		G_MARKUP_COLLECT_BOOLEAN,
		"encrypt-to-self", &encrypt_to_self,
		G_MARKUP_COLLECT_STRING |
		G_MARKUP_COLLECT_OPTIONAL,
		"hash-algo", &hash_algo,
		G_MARKUP_COLLECT_BOOLEAN,
		"sign-default", &sign_default,
		G_MARKUP_COLLECT_INVALID);

	if (!success)
		return;

	g_key_file_set_boolean (
		parse_data->identity_key_file,
		E_SOURCE_EXTENSION_SMIME,
		"EncryptByDefault", encrypt_default);

	g_key_file_set_boolean (
		parse_data->identity_key_file,
		E_SOURCE_EXTENSION_SMIME,
		"EncryptToSelf", encrypt_to_self);

	if (hash_algo != NULL && *hash_algo != '\0')
		g_key_file_set_string (
			parse_data->identity_key_file,
			E_SOURCE_EXTENSION_SMIME,
			"SigningAlgorithm", hash_algo);

	g_key_file_set_boolean (
		parse_data->identity_key_file,
		E_SOURCE_EXTENSION_SMIME,
		"SignByDefault", sign_default);
}
