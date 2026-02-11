cmd_unmerge_cells (WorkbookControl *wbc, Sheet *sheet, GSList const *selection)
{
	CmdUnmergeCells *me;
	char *names;

	g_return_val_if_fail (IS_SHEET (sheet), TRUE);

	me = g_object_new (CMD_UNMERGE_CELLS_TYPE, NULL);

	me->cmd.sheet = sheet;
	me->cmd.size = 1;

	names = undo_range_list_name (sheet, selection);
	me->cmd.cmd_descriptor = g_strdup_printf (_("Unmerging %s"), names);
	g_free (names);

	me->unmerged_regions = NULL;
	me->ranges = g_array_new (FALSE, FALSE, sizeof (GnmRange));
	for ( ; selection != NULL ; selection = selection->next) {
		GSList *merged = gnm_sheet_merge_get_overlap (sheet, selection->data);
		if (merged != NULL) {
			g_array_append_val (me->ranges, *(GnmRange *)selection->data);
			g_slist_free (merged);
		}
	}

	if (me->ranges->len <= 0) {
		g_object_unref (me);
		return TRUE;
	}

	return gnm_command_push_undo (wbc, G_OBJECT (me));
}
