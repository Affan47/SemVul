on_revision_dnd (GitgRevision *source,
                 GitgRef      *dest,
                 gboolean      dropped,
                 GitgWindow   *window)
{
	if (!dropped)
	{
		update_revision_dnd_status (window, source, dest);
		return FALSE;
	}

	if (gitg_ref_get_ref_type (dest) != GITG_REF_TYPE_BRANCH)
	{
		return FALSE;
	}

	return gitg_window_add_branch_action (window,
	                                      gitg_branch_actions_cherry_pick (window, source, dest));
}
