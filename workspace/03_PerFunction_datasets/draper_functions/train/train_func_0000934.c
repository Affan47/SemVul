cmd_hyperlink_redo (GnmCommand *cmd, WorkbookControl *wbc)
{
	CmdHyperlink *me = CMD_HYPERLINK (cmd);
	GSList *l;
	Workbook *wb = wb_control_get_workbook (wbc);

	g_return_val_if_fail (me != NULL, TRUE);


	if (cmd_selection_is_locked_effective (me->cmd.sheet, me->selection,
					       wbc, _("Changing Hyperlink")))
		return TRUE;

	for (l = me->selection; l; l = l->next) {
		GnmRange const *r = l->data;

		if (me->new_style) {
			gnm_style_ref (me->new_style);
			sheet_apply_style (me->cmd.sheet, r, me->new_style);
		}

		sheet_flag_style_update_range (me->cmd.sheet, r);
	}

	if (me->opt_content != NULL)
		for (l = me->cells; l; l = l->next) {
			GnmCell *cell = l->data;
			sheet_cell_set_value (cell, value_new_string (me->opt_content));
		}


	sheet_redraw_all (me->cmd.sheet, FALSE);
	sheet_mark_dirty (me->cmd.sheet);

	select_selection (me->cmd.sheet, me->selection, wbc);

	WORKBOOK_FOREACH_CONTROL (wb, view, ctl,
			wb_control_menu_state_update (ctl, MS_COMMENT_LINKS););

	return FALSE;
}
