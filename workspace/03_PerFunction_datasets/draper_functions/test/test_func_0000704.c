cmdnames_find (GList *list, gchar **v)
{
	GList *it;

	if (v == NULL || *v == NULL) {
		return list;
	}

	for (it = g_list_first (list); it != NULL; it = g_list_next (it)) {
		command_name_t *cmd = it->data;
		if (!strcmp (*v, cmd->name)) {
			return cmdnames_find (cmd->subcommands, v+1);
		}
	}

	return NULL;
}
