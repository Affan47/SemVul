provider_list_free (gpointer data)
{
	GSList *list = (GSList *) data;

	while (list) {
		nma_mobile_provider_unref ((NMAMobileProvider *) list->data);
		list = g_slist_delete_link (list, list);
	}
}
