vis_init(void) {
	if (!(cmdmap = map_new()))
		return false;
	for (Command *cmd = cmds; cmd && cmd->name[0]; cmd++) {
		for (const char **name = cmd->name; *name; name++) {
			if (!map_put(cmdmap, *name, cmd))
				return false;
		}
	}
	return true;
}
