views_cache_discover_parent_for_children(viewEntry *pView)
{
	int ii = 0;

	for (ii = 0; pView->pChildren && (ii < pView->child_count); ++ii)
	{
		viewEntry *current = (viewEntry *)pView->pChildren[ii];
		views_cache_discover_parent(current);
	}
}
