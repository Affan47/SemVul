dns_lookup_create(isc_mem_t *mctx, dns_name_t *name, dns_rdatatype_t type,
		  dns_view_t *view, unsigned int options, isc_task_t *task,
		  isc_taskaction_t action, void *arg, dns_lookup_t **lookupp)
{
	isc_result_t result;
	dns_lookup_t *lookup;
	isc_event_t *ievent;

	lookup = isc_mem_get(mctx, sizeof(*lookup));
	if (lookup == NULL)
		return (ISC_R_NOMEMORY);
	lookup->mctx = NULL;
	isc_mem_attach(mctx, &lookup->mctx);
	lookup->options = options;

	ievent = isc_event_allocate(mctx, lookup, DNS_EVENT_LOOKUPDONE,
				    action, arg, sizeof(*lookup->event));
	if (ievent == NULL) {
		result = ISC_R_NOMEMORY;
		goto cleanup_lookup;
	}
	lookup->event = (dns_lookupevent_t *)ievent;
	lookup->event->ev_destroy = levent_destroy;
	lookup->event->ev_destroy_arg = mctx;
	lookup->event->result = ISC_R_FAILURE;
	lookup->event->name = NULL;
	lookup->event->rdataset = NULL;
	lookup->event->sigrdataset = NULL;
	lookup->event->db = NULL;
	lookup->event->node = NULL;

	lookup->task = NULL;
	isc_task_attach(task, &lookup->task);

	result = isc_mutex_init(&lookup->lock);
	if (result != ISC_R_SUCCESS)
		goto cleanup_event;

	dns_fixedname_init(&lookup->name);

	result = dns_name_copy(name, dns_fixedname_name(&lookup->name), NULL);
	if (result != ISC_R_SUCCESS)
		goto cleanup_lock;

	lookup->type = type;
	lookup->view = NULL;
	dns_view_attach(view, &lookup->view);
	lookup->fetch = NULL;
	lookup->restarts = 0;
	lookup->canceled = ISC_FALSE;
	dns_rdataset_init(&lookup->rdataset);
	dns_rdataset_init(&lookup->sigrdataset);
	lookup->magic = LOOKUP_MAGIC;

	*lookupp = lookup;

	lookup_find(lookup, NULL);

	return (ISC_R_SUCCESS);

 cleanup_lock:
	DESTROYLOCK(&lookup->lock);

 cleanup_event:
	ievent = (isc_event_t *)lookup->event;
	isc_event_free(&ievent);
	lookup->event = NULL;

	isc_task_detach(&lookup->task);

 cleanup_lookup:
	isc_mem_putanddetach(&mctx, lookup, sizeof(*lookup));

	return (result);
}
