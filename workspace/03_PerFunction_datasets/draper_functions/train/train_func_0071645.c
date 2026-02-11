e_util_get_category_filter_options (void)
{
	GSList *res = NULL;
	GList *clist, *l;

	clist = e_categories_get_list ();
	for (l = clist; l; l = l->next) {
		const gchar *cname = l->data;
		struct _filter_option *fo;

		if (!e_categories_is_searchable (cname))
			continue;

		fo = g_new0 (struct _filter_option, 1);

		fo->title = g_strdup (cname);
		fo->value = g_strdup (cname);
		res = g_slist_prepend (res, fo);
	}

	g_list_free (clist);

	return g_slist_reverse (res);
}
