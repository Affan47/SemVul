gw_disk_get_total_folders ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *child = NULL;
	int n = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	child = GTK_CTREE_ROW( node)->children;
	while ( child != NULL )
	{
		n++;
		n = n + gw_disk_get_total_folders ( ctree, child);
		child = GTK_CTREE_ROW ( child)->sibling;
	}

	return n;
}
