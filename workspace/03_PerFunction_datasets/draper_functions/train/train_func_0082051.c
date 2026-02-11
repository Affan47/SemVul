fr_command_info_free (FrCommandInfo *info)
{
	if (info == NULL)
		return;

	if (info->args != NULL) {
		g_list_foreach (info->args, (GFunc) g_free, NULL);
		g_list_free (info->args);
		info->args = NULL;
	}

	if (info->dir != NULL) {
		g_free (info->dir);
		info->dir = NULL;
	}

	g_free (info);
}
