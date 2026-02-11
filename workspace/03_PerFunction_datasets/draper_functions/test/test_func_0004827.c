MGD77_Path_Free (int n, char **list)
{
	int i;
#ifdef DEBUG
	GMT_LONG change = FALSE;
#endif
	if (n == 0) return;

#ifdef DEBUG

	if (GMT_mem_keeper->active) {
		GMT_memtrack_off (GMT_mem_keeper);
		change = TRUE;
	}
#endif
	for (i = 0; i < n; i++) GMT_free ((void *)list[i]);
	GMT_free ((void *)list);
#ifdef DEBUG
	if (change) GMT_memtrack_on (GMT_mem_keeper);
#endif
}
