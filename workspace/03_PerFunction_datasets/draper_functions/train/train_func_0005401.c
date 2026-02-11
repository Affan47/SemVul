destroy(dns_adb_t *adb) {
	adb->magic = 0;

	isc_task_detach(&adb->task);

	isc_mempool_destroy(&adb->nmp);
	isc_mempool_destroy(&adb->nhmp);
	isc_mempool_destroy(&adb->limp);
	isc_mempool_destroy(&adb->emp);
	isc_mempool_destroy(&adb->ahmp);
	isc_mempool_destroy(&adb->aimp);
	isc_mempool_destroy(&adb->afmp);

	DESTROYMUTEXBLOCK(adb->entrylocks, adb->nentries);
	isc_mem_put(adb->mctx, adb->entries,
		    sizeof(*adb->entries) * adb->nentries);
	isc_mem_put(adb->mctx, adb->deadentries,
		    sizeof(*adb->deadentries) * adb->nentries);
	isc_mem_put(adb->mctx, adb->entrylocks,
		    sizeof(*adb->entrylocks) * adb->nentries);
	isc_mem_put(adb->mctx, adb->entry_sd,
		    sizeof(*adb->entry_sd) * adb->nentries);
	isc_mem_put(adb->mctx, adb->entry_refcnt,
		    sizeof(*adb->entry_refcnt) * adb->nentries);

	DESTROYMUTEXBLOCK(adb->namelocks, adb->nnames);
	isc_mem_put(adb->mctx, adb->names,
		    sizeof(*adb->names) * adb->nnames);
	isc_mem_put(adb->mctx, adb->deadnames,
		    sizeof(*adb->deadnames) * adb->nnames);
	isc_mem_put(adb->mctx, adb->namelocks,
		    sizeof(*adb->namelocks) * adb->nnames);
	isc_mem_put(adb->mctx, adb->name_sd,
		    sizeof(*adb->name_sd) * adb->nnames);
	isc_mem_put(adb->mctx, adb->name_refcnt,
		    sizeof(*adb->name_refcnt) * adb->nnames);

	DESTROYLOCK(&adb->reflock);
	DESTROYLOCK(&adb->lock);
	DESTROYLOCK(&adb->mplock);
	DESTROYLOCK(&adb->overmemlock);
	DESTROYLOCK(&adb->entriescntlock);
	DESTROYLOCK(&adb->namescntlock);

	isc_mem_putanddetach(&adb->mctx, adb, sizeof(dns_adb_t));
}
