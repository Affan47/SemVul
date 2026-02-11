hardfile_reset (void)
{
	int i, j;
	struct hardfileprivdata *hfpd;

	for (i = 0; i < MAX_FILESYSTEM_UNITS; i++) {
		hfpd = &hardfpd[i];
		if (hfpd->base && valid_address (hfpd->base, 36) && get_word (hfpd->base + 32) > 0) {
			for (j = 0; j < MAX_ASYNC_REQUESTS; j++) {
				uaecptr request;
				if ((request = hfpd->d_request[i]))
					abort_async (hfpd, request, 0, 0);
			}
		}
		memset (hfpd, 0, sizeof (struct hardfileprivdata));
	}
}
