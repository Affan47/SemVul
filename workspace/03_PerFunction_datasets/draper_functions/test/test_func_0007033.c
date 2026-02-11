temp_files_undo(GSList *tlist, GSList *slist, GtkTreeModel *model)
{
	GSList		*titer, *siter;

	for(titer = tlist, siter = slist; titer != NULL; titer = g_slist_next(titer), siter = g_slist_next(siter))
	{
		if(titer->data != NULL)
			temp_file_undo(titer, siter, model);
	}
}
