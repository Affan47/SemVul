free_args (GSList *list)
{
	GSList *li;

	for (li = list; li != NULL; li = li->next) {
		g_object_unref (G_FILE (li->data));
		li->data = NULL;
	}
	g_slist_free (list);
}
