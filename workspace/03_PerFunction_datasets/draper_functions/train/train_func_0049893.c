camel_iconv_close (iconv_t ip)
{
	struct _iconv_cache_node *in;

	if (ip == (iconv_t) - 1)
		return;

	G_LOCK (iconv);
	in = g_hash_table_lookup (iconv_cache_open, ip);
	if (in) {
		cd (printf ("closing iconv converter '%s'\n", in->parent->conv));
		g_queue_remove (&in->parent->open, in);
		in->busy = FALSE;
		g_queue_push_tail (&in->parent->open, in);
	} else {
		g_warning ("trying to close iconv i dont know about: %p", ip);
		iconv_close (ip);
	}
	G_UNLOCK (iconv);
}
