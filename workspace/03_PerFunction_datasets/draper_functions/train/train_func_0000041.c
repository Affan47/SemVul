cmd_objects_delete_undo (GnmCommand *cmd,
			G_GNUC_UNUSED WorkbookControl *wbc)
{
	CmdObjectsDelete *me = CMD_OBJECTS_DELETE (cmd);
	GSList *l;
	gint i;

	g_slist_foreach (me->objects,
		(GFunc) sheet_object_set_sheet, me->cmd.sheet);

	for (l = me->objects, i = 0; l; l = l->next, i++)
		cmd_objects_restore_location (SHEET_OBJECT (l->data),
					      g_array_index(me->location,
							    gint, i));
	return FALSE;
}
