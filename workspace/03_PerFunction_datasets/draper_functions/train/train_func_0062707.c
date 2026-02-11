skype_get_public_alias(PurpleConnection *gc, _account_char_fn success_cb, _account_char_fn failure_cb)
{
	struct _skype_account_alias_cb *info;
	gchar *alias;

	info = g_new0(struct _skype_account_alias_cb, 1);
	alias = skype_send_message("GET PROFILE FULLNAME");

	info = g_new0(struct _skype_account_alias_cb, 1);
	info->callback = success_cb;
	info->account = gc->account;
	info->message = g_strdup(&alias[16]);

	purple_timeout_add(0, skype_account_alias_cb, info);

	g_free(alias);
}
