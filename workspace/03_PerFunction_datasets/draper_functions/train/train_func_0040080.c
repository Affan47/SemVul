imapx_server_stash_command_arguments (CamelIMAPXServer *is)
{
	GString *buffer;


	buffer = g_string_new ("MESSAGES UNSEEN UIDVALIDITY UIDNEXT");
	if (CAMEL_IMAPX_HAVE_CAPABILITY (is->cinfo, CONDSTORE))
		g_string_append (buffer, " HIGHESTMODSEQ");
	g_free (is->priv->status_data_items);
	is->priv->status_data_items = g_string_free (buffer, FALSE);
}
