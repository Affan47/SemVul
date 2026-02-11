cmd_clearsize(MainInfo *min, DirPane *src, DirPane *dst, const CmdArg *ca)
{
	GtkTreeModel	*m = dp_get_tree_model(src);
	GSList		*slist, *iter;
	guint		num = 0;
	GError		*err = NULL;
	gboolean	ok = TRUE;

	if((slist = dp_get_selection(src)) == NULL)
		return 1;

	for(iter = slist; ok && (iter != NULL); iter = g_slist_next(iter))
	{
		if(dp_row_get_file_type(m, iter->data, TRUE) == G_FILE_TYPE_DIRECTORY && dp_row_get_flags(m, iter->data, DPRF_HAS_SIZE))
		{


			ok = dp_rescan_row(src, iter->data, &err);
			if(!ok)
				err_set_gerror(min, &err, CMD_ID2, dp_get_file_from_row(src, iter->data));
			num++;
		}
		if(getsize_options.unselect)
			dp_unselect(src, iter->data);
	}
	dp_free_selection(slist);

	if(num)
	{
		dp_update_stats(src);
		dp_show_stats(src);
	}
	return ok;
}
