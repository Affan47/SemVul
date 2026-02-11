camel_cipher_validity_set_description (CamelCipherValidity *validity,
                                       const gchar *description)
{
	g_return_if_fail (validity != NULL);

	g_free (validity->sign.description);
	validity->sign.description = g_strdup (description);
}
