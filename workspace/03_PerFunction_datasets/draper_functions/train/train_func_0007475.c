tm_project_remove_object(TMProject *project, TMWorkObject *w)
{
	guint i;

	g_return_val_if_fail((project && w), FALSE);
	if (!project->file_list)
		return FALSE;
	for (i=0; i < project->file_list->len; ++i)
	{
		if (w == project->file_list->pdata[i])
		{
			tm_work_object_free(w);
			g_ptr_array_remove_index(project->file_list, i);
			tm_project_update(TM_WORK_OBJECT(project), TRUE, FALSE, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}
