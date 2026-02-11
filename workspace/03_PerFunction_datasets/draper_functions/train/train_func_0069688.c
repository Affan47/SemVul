file_is_visible (GthSearchTask *task,
		 GFileInfo     *info)
{
	if (task->priv->show_hidden_files)
		return TRUE;
	else
		return ! g_file_info_get_is_hidden (info);

}
