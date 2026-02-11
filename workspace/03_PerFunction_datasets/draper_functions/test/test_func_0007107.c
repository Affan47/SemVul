tm_project_autoscan(TMProject *project)
{
	TMFileEntry *root_dir;
	GList *file_match;
	GList *dir_unmatch;

	file_match = glist_from_array(project->sources);
	dir_unmatch = glist_from_array(project->ignore);

	if (!project || !IS_TM_PROJECT(TM_WORK_OBJECT(project))
	  || (!project->dir))
		return FALSE;
	if (!(root_dir = tm_file_entry_new(project->dir, NULL, TRUE
		, file_match, NULL, NULL, dir_unmatch, TRUE, TRUE)))
	{
		g_warning("Unable to create file entry");
		return FALSE;
	}
	g_list_free(file_match);
	g_list_free(dir_unmatch);
	tm_file_entry_foreach(root_dir, tm_project_add_file_recursive
	  , project, 0, FALSE);
	tm_file_entry_free(root_dir);
	tm_project_update(TM_WORK_OBJECT(project), TRUE, FALSE, TRUE);
	return TRUE;
}
