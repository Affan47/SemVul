e_attachment_is_rfc822 (EAttachment *attachment)
{
	gchar *mime_type;
	gboolean is_rfc822;

	g_return_val_if_fail (E_IS_ATTACHMENT (attachment), FALSE);

	mime_type = e_attachment_dup_mime_type (attachment);
	is_rfc822 =
		(mime_type != NULL) &&
		(g_ascii_strcasecmp (mime_type, "message/rfc822") == 0);
	g_free (mime_type);

	return is_rfc822;
}
