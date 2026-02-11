build_read_commands(BuildDestination *dst, BuildTableData table_data, gint response)
{
	guint cmdindex, cmd;
	gboolean changed = FALSE;

	if (response == GTK_RESPONSE_ACCEPT)
	{
		for (cmdindex = 0, cmd = 0; cmd < build_groups_count[GEANY_GBG_FT]; ++cmdindex, ++cmd)
			changed |= read_row(dst, table_data, cmdindex, GEANY_GBG_FT, cmd);
		for (cmd = 0; cmd < build_groups_count[GEANY_GBG_NON_FT]; ++cmdindex, ++cmd)
			changed |= read_row(dst, table_data, cmdindex, GEANY_GBG_NON_FT, cmd);
		for (cmd = 0; cmd < build_groups_count[GEANY_GBG_EXEC]; ++cmdindex, ++cmd)
			changed |= read_row(dst, table_data, cmdindex, GEANY_GBG_EXEC, cmd);
		changed |= read_regex(table_data->fileregex, table_data->fileregexstring, dst->fileregexstr);
		changed |= read_regex(table_data->nonfileregex, table_data->nonfileregexstring, dst->nonfileregexstr);
	}
	return changed;
}
