cmd_zoom_undo (GnmCommand *cmd,
	       G_GNUC_UNUSED WorkbookControl *wbc)
{
	CmdZoom *me = CMD_ZOOM (cmd);
	GSList *l;
	int i;

	g_return_val_if_fail (me != NULL, TRUE);
	g_return_val_if_fail (me->sheets != NULL, TRUE);
	g_return_val_if_fail (me->old_factors != NULL, TRUE);

	for (i = 0, l = me->sheets; l != NULL; l = l->next, i++) {
		Sheet *sheet = l->data;
		g_object_set (sheet, "zoom-factor", me->old_factors[i], NULL);
	}

	return FALSE;
}
