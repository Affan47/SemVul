uhc_get_next(void)
{
	struct uhc *uhc;
	char *host;
	time_t now;

	g_return_val_if_fail(uhc_list, NULL);

	now = tm_time();
	uhc = hash_list_head(uhc_list);
	if (NULL == uhc)
		return NULL;


	if (uhc->stamp && delta_time(now, uhc->stamp) < UHC_RETRY_AFTER)
		return NULL;

	uhc->stamp = now;
	host = h_strdup(uhc->host);

	if (uhc->used < UHC_MAX_ATTEMPTS) {
		uhc->used++;
		hash_list_moveto_tail(uhc_list, uhc);
	} else {
		hash_list_remove(uhc_list, uhc);
		uhc_free(&uhc);
	}

	return host;
}
