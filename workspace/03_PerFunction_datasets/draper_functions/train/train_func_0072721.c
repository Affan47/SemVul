driver_free(void)
{
	upstype_t	*ups, *unext;

	for (ups = firstups; ups; ups = unext) {
		unext = ups->next;

		if (ups->sock_fd != -1) {
			close(ups->sock_fd);
		}

		sstate_infofree(ups);
		sstate_cmdfree(ups);

		pconf_finish(&ups->sock_ctx);

		free(ups->fn);
		free(ups->name);
		free(ups->desc);
		free(ups);
	}
}
