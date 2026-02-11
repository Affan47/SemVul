camel_cipher_validity_clear (CamelCipherValidity *validity)
{
	g_return_if_fail (validity != NULL);


	g_free (validity->sign.description);
	g_free (validity->encrypt.description);
	camel_cipher_validity_init (validity);
}
