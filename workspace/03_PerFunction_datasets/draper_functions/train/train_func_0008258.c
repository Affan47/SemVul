cmd_goal_seek (WorkbookControl *wbc, GnmCell *cell, GnmValue *ov, GnmValue *nv)
{
	CmdGoalSeek *me;
	GnmRange range;

	g_return_val_if_fail (cell != NULL, TRUE);
	g_return_val_if_fail (ov != NULL || nv != NULL, TRUE);

	me = g_object_new (CMD_GOAL_SEEK_TYPE, NULL);

	me->cmd.sheet = cell->base.sheet;
	me->cmd.size = 1;
	range_init_cellpos (&range, &cell->pos);
	me->cmd.cmd_descriptor = g_strdup_printf
		(_("Goal Seek (%s)"), undo_range_name (cell->base.sheet, &range));

	me->cell = cell;
	me->ov = ov;
	me->nv = nv;

	if (me->ov == NULL)
		me->ov = value_dup (cell->value);
	if (me->nv == NULL)
		me->nv = value_dup (cell->value);

	return gnm_command_push_undo (wbc, G_OBJECT (me));
}
