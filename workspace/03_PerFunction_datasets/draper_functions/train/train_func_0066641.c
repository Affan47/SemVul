enchant_dict_check (EnchantDict * dict, const char *const word, ssize_t len)
{
	EnchantSession * session;

	g_return_val_if_fail (dict, -1);
	g_return_val_if_fail (word, -1);

	if (len < 0)
		len = strlen (word);

	g_return_val_if_fail (len, -1);
	g_return_val_if_fail (g_utf8_validate(word, len, NULL),-1);

	session = ((EnchantDictPrivateData*)dict->enchant_private_data)->session;
	enchant_session_clear_error (session);


	if (enchant_session_exclude (session, word, len))
		return 1;


	if (enchant_session_contains(session, word, len))
		return 0;

	if (dict->check)
		return (*dict->check) (dict, word, len);
	else if (session->is_pwl)
		return 1;

	return -1;
}
