ForgetBackgroundWorker(slist_mutable_iter *cur)
{
	RegisteredBgWorker *rw;
	BackgroundWorkerSlot *slot;

	rw = slist_container(RegisteredBgWorker, rw_lnode, cur->cur);

	Assert(rw->rw_shmem_slot < max_worker_processes);
	slot = &BackgroundWorkerData->slot[rw->rw_shmem_slot];
	slot->in_use = false;

	ereport(DEBUG1,
			(errmsg("unregistering background worker \"%s\"",
					rw->rw_worker.bgw_name)));

	slist_delete_current(cur);
	free(rw);
}
