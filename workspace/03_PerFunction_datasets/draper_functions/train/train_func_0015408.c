e_source_authenticator_get_prompt_strings (ESourceAuthenticator *auth,
                                           ESource *source,
                                           gchar **prompt_title,
                                           gchar **prompt_message,
                                           gchar **prompt_description)
{
	ESourceAuthenticatorInterface *interface;

	g_return_if_fail (E_IS_SOURCE_AUTHENTICATOR (auth));
	g_return_if_fail (E_IS_SOURCE (source));
	g_return_if_fail (prompt_title != NULL);
	g_return_if_fail (prompt_message != NULL);
	g_return_if_fail (prompt_description != NULL);

	interface = E_SOURCE_AUTHENTICATOR_GET_INTERFACE (auth);
	g_return_if_fail (interface->get_prompt_strings);

	interface->get_prompt_strings (
		auth, source,
		prompt_title,
		prompt_message,
		prompt_description);
}
