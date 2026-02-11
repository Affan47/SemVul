iterator_begin(listmgr_t *L, int id, int sorted)
{
	if(id < 0 || id >= LISTMGR_NUM_CUR_NODES)
	{
		internal("listmgr: in priv iterator_begin(), id=%d exceeds NUM_CUR_NODES.",id);
		return NULL;
	}

	if(sorted)
		L->cur_node[id] = L->head_sorted;
	else
		L->cur_node[id] = L->head;

	return L->cur_node[id];
}
