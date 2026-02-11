ar_carini_getpath(GQueue *queue)
{
	gchar *tmp, *path = NULL;
	gint32 i;

	for(i = 0; i < g_queue_get_length(queue); i ++)
	{
		if(path == NULL)
			path = g_strdup((gchar *)g_queue_peek_nth(queue, i));
		else
		{
			tmp = g_strdup_printf("%s.%s",
				(gchar *)g_queue_peek_nth(queue, i), path);
			g_free(path);
			path = tmp;
		}
	}

	return path;
}
