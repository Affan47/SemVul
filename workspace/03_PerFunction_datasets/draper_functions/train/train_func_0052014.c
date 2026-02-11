char_is_invisible (const GtkTextIter *iter)
{
	GSList *tags;
	gboolean invisible = FALSE;
	tags = gtk_text_iter_get_tags (iter);
	while (tags)
	{
		gboolean this_invisible, invisible_set;
		g_object_get (tags->data, "invisible", &this_invisible,
			      "invisible-set", &invisible_set, NULL);
		if (invisible_set)
			invisible = this_invisible;
		tags = g_slist_delete_link (tags, tags);
	}
	return invisible;
}
