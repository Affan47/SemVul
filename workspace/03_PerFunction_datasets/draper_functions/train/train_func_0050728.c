cmd_selection_hyperlink (WorkbookControl *wbc,
			 GnmStyle *style,
			 char const *opt_translated_name,
			 char *opt_content)
{
	CmdHyperlink *me;
	GSList    *l;
	SheetView *sv = wb_control_cur_sheet_view (wbc);

	me = g_object_new (CMD_HYPERLINK_TYPE, NULL);

	me->selection  = selection_get_ranges (sv, FALSE);
	me->new_style  = style;

	me->cmd.sheet = sv_sheet (sv);
	me->cmd.size = 1;

	me->old_styles = NULL;
	me->cells = NULL;
	me->opt_content = opt_content;
	for (l = me->selection; l; l = l->next) {
		GnmRange const *sel_r = l->data;
		GnmRange r = *sel_r;
		CmdHyperlinkOldStyle *os;

		os = g_new (CmdHyperlinkOldStyle, 1);

		os->styles = sheet_style_get_range (me->cmd.sheet, &r);
		os->pos = r.start;

		me->cmd.size += g_slist_length (os->styles);
		me->old_styles = g_slist_append (me->old_styles, os);

		if (opt_content != NULL)
			sheet_foreach_cell_in_range (me->cmd.sheet, CELL_ITER_ALL,
						     r.start.col, r.start.row,
						     r.end.col, r.end.row,
						     cb_cmd_hyperlink_find_cells,
						     &me->cells);
		me->cmd.size += g_slist_length (me->cells)/2;
	}

	if (opt_translated_name == NULL) {
		char *names = undo_range_list_name (me->cmd.sheet, me->selection);

		me->cmd.cmd_descriptor = g_strdup_printf (_("Changing hyperlink of %s"), names);
		g_free (names);
	} else
		me->cmd.cmd_descriptor = g_strdup (opt_translated_name);


	return gnm_command_push_undo (wbc, G_OBJECT (me));
}
