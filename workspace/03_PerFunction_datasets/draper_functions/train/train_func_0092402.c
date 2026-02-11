project_list_sort(GList *prjs, int (cmp)(const void *, const void *))
{
	GList *node;
	prjs = g_list_sort (prjs, cmp);
	for (node = prjs; node; node=node->next)
	{
		GttProject *prj = node->data;
		if (prj->sub_projects)
		{
			prj->sub_projects = project_list_sort (prj->sub_projects, cmp);
		}
	}
	return prjs;
}
