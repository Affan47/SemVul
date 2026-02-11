vcal_free_data_func(GNode *node, gpointer user_data)
{
	VCalFolderItem *item = node->data;

	if (item->cal) {
		icalcomponent_free(item->cal);
		item->cal = NULL;
	}
	if (item->numlist) {
		g_slist_free(item->numlist);
		item->numlist = NULL;
	}

	if (item->evtlist) {
		slist_free_icalfeeddata(item->evtlist);
		g_slist_free(item->evtlist);
		item->evtlist = NULL;
	}

	return FALSE;
}
