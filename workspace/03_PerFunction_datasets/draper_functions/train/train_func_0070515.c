listmgr_sort_descending(listmgr_t *L)


{
	if(L == NULL)
	{
		internal("listmgr: in sort_descending(), list is NULL.");
		return;
	}

	if(L->compare == NULL)
		internal("listmgr: in sort_descending(), no compare function set.");

	sort_list(L, -1);
}
