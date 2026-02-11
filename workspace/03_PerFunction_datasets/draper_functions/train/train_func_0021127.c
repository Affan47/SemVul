camel_imapx_parse_mailbox (CamelIMAPXStream *is,
                           gchar separator,
                           GCancellable *cancellable,
                           GError **error)
{
	guchar *token;
	gchar *mailbox_name;

	g_return_val_if_fail (CAMEL_IS_IMAPX_STREAM (is), NULL);

	if (!camel_imapx_stream_astring (is, &token, cancellable, error))
		return NULL;

	mailbox_name = camel_utf7_utf8 ((gchar *) token);

	camel_imapx_normalize_mailbox (mailbox_name, separator);

	return mailbox_name;
}
