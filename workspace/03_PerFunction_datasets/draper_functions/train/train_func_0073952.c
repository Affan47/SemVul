cmd_merge_cells_undo (GnmCommand *cmd, WorkbookControl *wbc)
{
	CmdMergeCells *me = CMD_MERGE_CELLS (cmd);
	unsigned i, flags;

	g_return_val_if_fail (me != NULL, TRUE);

	for (i = 0 ; i < me->ranges->len ; ++i) {
		GnmRange const *r = &(g_array_index (me->ranges, GnmRange, i));
		gnm_sheet_merge_remove (me->cmd.sheet, r, GO_CMD_CONTEXT (wbc));
	}


	flags = PASTE_CONTENTS | PASTE_FORMATS | PASTE_COMMENTS |
		PASTE_IGNORE_COMMENTS_AT_ORIGIN;
	if (me->center)
		flags |= PASTE_FORMATS;
	for (i = 0 ; i < me->ranges->len ; ++i) {
		GnmRange const *r = &(g_array_index (me->ranges, GnmRange, i));
		GnmPasteTarget pt;
		GnmCellRegion * c;

		g_return_val_if_fail (me->old_contents != NULL, TRUE);

		c = me->old_contents->data;
		clipboard_paste_region (c,
			paste_target_init (&pt, me->cmd.sheet, r, flags),
			GO_CMD_CONTEXT (wbc));
		cellregion_unref (c);
		me->old_contents = g_slist_remove (me->old_contents, c);
	}
	g_return_val_if_fail (me->old_contents == NULL, TRUE);

	return FALSE;
}
