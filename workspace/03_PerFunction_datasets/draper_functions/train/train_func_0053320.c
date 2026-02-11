maki_server_rename_user (makiServer* serv, gchar const* old_nick, gchar const* new_nick)
{
	makiUser* user;
	gchar* tmp = NULL;
	gboolean ret = TRUE;

	g_return_val_if_fail(serv != NULL, FALSE);
	g_return_val_if_fail(old_nick != NULL, FALSE);
	g_return_val_if_fail(new_nick != NULL, FALSE);

	g_mutex_lock(serv->mutex.users);

	if (g_hash_table_lookup(serv->users, new_nick) != NULL)
	{
		ret = FALSE;
		goto end;
	}

	if ((user = g_hash_table_lookup(serv->users, old_nick)) == NULL)
	{
		ret = FALSE;
		goto end;
	}


	tmp = g_strdup(old_nick);

	maki_user_set_nick(user, new_nick);

	g_hash_table_insert(serv->users, g_strdup(new_nick), user);
	g_hash_table_remove(serv->users, tmp);

end:
	g_free(tmp);

	g_mutex_unlock(serv->mutex.users);

	return ret;
}
