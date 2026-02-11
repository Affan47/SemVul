hashSha1_to_bin(const gchar *p_input, guint8 *p_digest)
{
	if(!p_digest)
		return;

	PurpleCipherContext *context;

	context = purple_cipher_context_new_by_name("sha1", NULL);
	if (context == NULL)
	{
		purple_debug_error("gfire", "Could not find sha1 cipher\n");
		return;
	}

	purple_cipher_context_append(context, (guchar*)p_input, strlen(p_input));
	if (!purple_cipher_context_digest(context, 20, p_digest, NULL))
	{
		purple_debug_error("gfire", "Failed to get SHA-1 digest.\n");
		return;
	}
	purple_cipher_context_destroy(context);
}
