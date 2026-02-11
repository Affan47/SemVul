cmd_text_to_columns (WorkbookControl *wbc,
		     GnmRange const *src, Sheet *src_sheet,
		     GnmRange const *target, Sheet *target_sheet,
		     GnmCellRegion *contents)
{
	CmdTextToColumns *me;
	char *src_range_name, *target_range_name;

	g_return_val_if_fail (contents != NULL, TRUE);

	src_range_name = undo_range_name (src_sheet, src);
	target_range_name = undo_range_name (target_sheet, target);

	me = g_object_new (CMD_TEXT_TO_COLUMNS_TYPE, NULL);

	me->cmd.sheet = (src_sheet == target_sheet ? src_sheet : NULL);
	me->cmd.size = 1;
	me->cmd.cmd_descriptor = g_strdup_printf (_("Text (%s) to Columns (%s)"),
						  src_range_name,
						  target_range_name);
	me->dst.range = *target;
	me->dst.sheet = target_sheet;
	me->dst.paste_flags = PASTE_CONTENTS | PASTE_FORMATS;
	me->src = *src;
	me->src_sheet = src_sheet;
	me->contents = contents;
	me->saved_sizes = NULL;

	g_free (src_range_name);
	g_free (target_range_name);


	if (sheet_range_splits_region (target_sheet, &me->dst.range,
				       NULL, GO_CMD_CONTEXT (wbc), me->cmd.cmd_descriptor)) {
		g_object_unref (me);
		return TRUE;
	}

	return gnm_command_push_undo (wbc, G_OBJECT (me));
}
