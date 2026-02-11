http_async_free(http_async_t *ha)
{
	http_async_t *hax;

	http_async_check(ha);
	g_assert(sl_outgoing);


	for (hax = ha;; hax = hax->parent) {
		if (!hax->parent)
			break;
	}

	g_assert(hax != NULL);
	g_assert(hax->parent == NULL);

	http_async_free_recursive(hax);
}
