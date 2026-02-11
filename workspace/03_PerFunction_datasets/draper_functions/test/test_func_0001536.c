views_cache_discover_children(viewEntry *pView)
{
	viewEntry *head = theCache.pCacheViews;
	viewEntry *current;
	int child_count = 0;
	int add_count = 0;

	if(pView->pChildren)
	{
		slapi_ch_free((void**)&pView->pChildren);
		pView->pChildren = NULL;
	}


	for(current = head; current != NULL; current = current->list.pNext)
	{
		if(slapi_dn_isparent(pView->pDn, current->pDn))
			child_count++;
	}


	pView->child_count = child_count;

	if (child_count > 0)
	{
		pView->pChildren = (void **)slapi_ch_calloc(child_count, sizeof(viewEntry*));


		for(current = head; current != NULL; current = current->list.pNext)
		{
			if(slapi_dn_isparent(pView->pDn, current->pDn))
			{
				((viewEntry**)pView->pChildren)[add_count] = current;
				add_count++;
			}
		}
	}
}
