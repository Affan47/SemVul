stop_sniff(void)
{
	struct list_iterator li;
	struct packet *p;
	struct sniff_info *si;
	struct sniff_log *slog;

	if (!sniffer_running) {
		printf("sniffer isn't running\n");
		return;
	}
	list_remove(&l_ifunc_tcp, &ifunc_sniff);

	while ((p = list_pop(&l_sniff_pkt))) {
		si = p->p_arg[MODULE_SNIFF];
		sniff_info_release(si);
		packet_free(p);
	}
	list_produce_done(&l_sniff_pkt);
	pthread_join(sniff_thr, NULL);

	list_lock(&l_sniff_db);
	list_iter_set(&li, &l_sniff_db);
	while ((si = list_iter_get(&li))) {
		while ((slog = list_pop(&si->log)))
			free_sniff_log(slog);
	}
	list_iter_end(&li);
	list_unlock(&l_sniff_db);

	sniffer_running = 0;
	printf("sniffer stopped\n");
}
