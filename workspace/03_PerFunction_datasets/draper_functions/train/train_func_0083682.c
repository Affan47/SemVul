_bt_spoolinit(Relation heap, Relation index, bool isunique, bool isdead)
{
	BTSpool    *btspool = (BTSpool *) palloc0(sizeof(BTSpool));
	int			btKbytes;

	btspool->heap = heap;
	btspool->index = index;
	btspool->isunique = isunique;


	btKbytes = isdead ? work_mem : maintenance_work_mem;
	btspool->sortstate = tuplesort_begin_index_btree(heap, index, isunique,
													 btKbytes, false);

	return btspool;
}
