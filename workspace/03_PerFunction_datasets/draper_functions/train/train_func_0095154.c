cairocmd_clear(cairocmd_t* cmd) {
	if (!cmd)
		return;
	free(cmd->text);
	cmd->text = NULL;
	if (cmd->xy)
		dl_free(cmd->xy);
	cmd->xy = NULL;
}
