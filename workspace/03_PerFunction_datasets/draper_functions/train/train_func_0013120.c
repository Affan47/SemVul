ctrl_mouse_get_list(CtrlInfo *ctrl)
{
	GSList	*list = NULL;

	if(ctrl != NULL)
	{
		GList	*iter;

		for(iter = ctrl->mouse; iter != NULL; iter = g_list_next(iter))
			list = g_slist_append(list, iter->data);
	}

	return list;
}
