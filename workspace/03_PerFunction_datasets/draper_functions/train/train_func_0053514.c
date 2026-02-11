has_local_ref (GitgWindow  *window,
               gchar const *name)
{
	GSList *refs = gitg_repository_get_refs (window->priv->repository);
	GSList *item;
	gboolean ret = FALSE;

	for (item = refs; item; item = g_slist_next (item))
	{
		GitgRef *ref = GITG_REF (item->data);

		if (gitg_ref_get_ref_type (ref) != GITG_REF_TYPE_BRANCH)
		{
			continue;
		}

		gchar const *nm = gitg_ref_get_shortname (ref);

		if (g_strcmp0 (name, nm) == 0)
		{
			ret = TRUE;
			break;
		}
	}

	g_slist_free_full (refs, (GDestroyNotify)gitg_ref_free);

	return ret;
}
