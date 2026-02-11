privacy_get_encrypt_data(const gchar *id, GSList *recp_names)
{
	PrivacySystem *system;
	gchar *ret = NULL;
	GSList *uniq_names = NULL, *cur;

	cm_return_val_if_fail(id != NULL, NULL);
	cm_return_val_if_fail(recp_names != NULL, NULL);

	system = privacy_get_system(id);
	if (system == NULL)
		return NULL;
	if (!system->can_encrypt)
		return NULL;
	if (system->get_encrypt_data == NULL)
		return NULL;

	for (cur = recp_names; cur; cur = cur->next) {
		if (!g_slist_find_custom(uniq_names, cur->data, (GCompareFunc)strcmp)) {
			uniq_names = g_slist_prepend(uniq_names, cur->data);
		}
	}
	ret = system->get_encrypt_data(uniq_names);

	g_slist_free(uniq_names);
	return ret;
}
