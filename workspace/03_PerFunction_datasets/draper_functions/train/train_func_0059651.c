uid_slist_to_ecalcomponentid_slist (GSList *uids)
{
	GSList *ids = NULL;
	const GSList *l;

	for (l = uids; l; l = l->next) {
		ECalComponentId *id = g_new0 (ECalComponentId, 1);
		id->uid = g_strdup (l->data);
		ids = g_slist_append (ids, id);
	}

	return ids;
}
