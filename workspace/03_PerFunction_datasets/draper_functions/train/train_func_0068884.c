vficon_selection_get_list_by_index(ViewFile *vf)
{
	GList *list = NULL;
	GList *work;

	work = VFICON(vf)->selection;
	while (work)
		{
		list = g_list_prepend(list, GINT_TO_POINTER(g_list_index(vf->list, work->data)));
		work = work->next;
		}

	return g_list_reverse(list);
}
