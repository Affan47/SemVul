cmd_unmerge_cells_finalize (GObject *cmd)
{
	CmdUnmergeCells *me = CMD_UNMERGE_CELLS (cmd);

	if (me->unmerged_regions != NULL) {
		g_array_free (me->unmerged_regions, TRUE);
		me->unmerged_regions = NULL;
	}
	if (me->ranges != NULL) {
		g_array_free (me->ranges, TRUE);
		me->ranges = NULL;
	}

	gnm_command_finalize (cmd);
}
