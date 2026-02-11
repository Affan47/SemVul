upnp_service_gslist_free_null(GSList **list_ptr)
{
	GSList *list = *list_ptr;

	if (list != NULL) {
		GSList *sl;

		GM_SLIST_FOREACH(list, sl) {
			upnp_service_free(sl->data);
		}
		g_slist_free(list);
		*list_ptr = NULL;
	}
}
