controlCount()
{
	GList *list = gControl::controlList();
	gControl *ctrl;
	int n = 0;

	while (list)
	{
		ctrl = (gControl *)list->data;
		if (ctrl->window() == this)
			n++;
		list = g_list_next(list);
	}

	return n;
}
