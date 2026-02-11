smtp_next_token (const gchar *buf)
{
	const guchar *token;

	token = (const guchar *) buf;
	while (*token && !isspace ((gint) *token))
		token++;

	while (*token && isspace ((gint) *token))
		token++;

	return (const gchar *) token;
}
