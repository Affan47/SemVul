gsf_infile_stdio_dup (GsfInput *src_input, G_GNUC_UNUSED GError **err)
{
	GList *ptr;
	GsfInfileStdio *src = GSF_INFILE_STDIO (src_input);

	GsfInfileStdio *dst = g_object_new (GSF_INFILE_STDIO_TYPE, NULL);
	dst->root = g_strdup (src->root);

	for (ptr = src->children; ptr != NULL ; ptr = ptr->next)
		dst->children = g_list_prepend (dst->children,
			g_strdup (ptr->data));
	dst->children = g_list_reverse (dst->children);
	return GSF_INPUT (dst);
}
