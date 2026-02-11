index_flush(struct index *idx)
{
	struct skiplist *list;

	list = idx->mtbls[idx->lsn];

	if (!list) {
		__DEBUG("ERROR: List<%d> is NULL", idx->lsn);
		return ;
	}

	sst_merge(idx->sst, idx->mtbls[0]);
	skiplist_free(idx->mtbls[0]);

	log_trunc(idx->log);

	list = skiplist_new(idx->max_mtbl_size);
	idx->mtbls[idx->lsn] = list;
}
