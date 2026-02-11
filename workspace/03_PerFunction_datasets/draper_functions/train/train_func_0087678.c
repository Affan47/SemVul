build_remove_menu_item(const GeanyBuildSource src, const GeanyBuildGroup grp, const gint cmd)
{
	GeanyBuildCommand *bc;
	guint i;

	bc = get_build_group(src, grp);
	if (bc == NULL)
		return;
	if (cmd < 0)
	{
		for (i = 0; i < build_groups_count[grp]; ++i)
			bc[i].exists = FALSE;
	}
	else if ((guint) cmd < build_groups_count[grp])
		bc[cmd].exists = FALSE;
}
