writenode(isc_task_t *task, isc_event_t *event) {
	isc_task_t *worker;
	sevent_t *sevent = (sevent_t *)event;

	worker = (isc_task_t *)event->ev_sender;
	dumpnode(dns_fixedname_name(sevent->fname), sevent->node);
	cleannode(gdb, gversion, sevent->node);
	dns_db_detachnode(gdb, &sevent->node);
	isc_mem_put(mctx, sevent->fname, sizeof(dns_fixedname_t));
	assignwork(task, worker);
	isc_event_free(&event);
}
