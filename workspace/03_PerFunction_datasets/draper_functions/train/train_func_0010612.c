get_menu_label (GSList *cmd_list)
{
	if (cmd_list != NULL) {
		GnmCommand *cmd = GNM_COMMAND (cmd_list->data);
		return cmd->cmd_descriptor;
	}

	return NULL;
}
