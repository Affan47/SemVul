mono_cq_create ()
{
	MonoCQ *cq;

	cq = g_new0 (MonoCQ, 1);
	MONO_GC_REGISTER_ROOT_SINGLE (cq->head);
	MONO_GC_REGISTER_ROOT_SINGLE (cq->tail);
	cq->head = mono_mlist_alloc ((MonoObject *) mono_cqitem_alloc ());
	cq->tail = cq->head;
	CQ_DEBUG ("Created %p", cq);
	return cq;
}
