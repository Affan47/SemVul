tm_workspace_update(TMWorkObject *workspace, gboolean force
  , gboolean recurse, gboolean UNUSED update_parent)
{
	guint i;
	gboolean update_tags = force;

#ifdef TM_DEBUG
	g_message("Updating workspace");
#endif

	if (workspace != TM_WORK_OBJECT(theWorkspace))
		return FALSE;
	if (NULL == theWorkspace)
		return TRUE;
	if ((recurse) && (theWorkspace->work_objects))
	{
		for (i=0; i < theWorkspace->work_objects->len; ++i)
		{
			if (TRUE == tm_work_object_update(TM_WORK_OBJECT(
				  theWorkspace->work_objects->pdata[i]), FALSE, TRUE, FALSE))
				update_tags = TRUE;
		}
	}
	if (update_tags)
		tm_workspace_recreate_tags_array();

	return update_tags;
}
