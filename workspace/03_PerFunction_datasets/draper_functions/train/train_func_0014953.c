concatenate_extensions(GSList* extensions)
{
	GSList* iter_ext;
	gchar* p_str = NULL;
	gchar* temp = NULL;

	for(iter_ext = extensions ; iter_ext != NULL ; iter_ext = iter_ext->next)
	{
		temp = p_str;
		p_str = g_strjoin(",", (const gchar*)(iter_ext->data), p_str, NULL);
		g_free(temp);
	}

	return p_str;
}
