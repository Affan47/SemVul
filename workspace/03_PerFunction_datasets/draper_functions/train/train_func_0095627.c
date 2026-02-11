init_pollers()
{
	int p;
	struct poller *bp;

	if ((fd_cache = (uint32_t *)calloc(1, sizeof(uint32_t) * global.maxsock)) == NULL)
		goto fail_cache;

	if ((fd_updt = (uint32_t *)calloc(1, sizeof(uint32_t) * global.maxsock)) == NULL)
		goto fail_updt;

	do {
		bp = NULL;
		for (p = 0; p < nbpollers; p++)
			if (!bp || (pollers[p].pref > bp->pref))
				bp = &pollers[p];

		if (!bp || bp->pref == 0)
			break;

		if (bp->init(bp)) {
			memcpy(&cur_poller, bp, sizeof(*bp));
			return 1;
		}
	} while (!bp || bp->pref == 0);
	return 0;

 fail_updt:
	free(fd_cache);
 fail_cache:
	return 0;
}
