install_element(node_type_t ntype, cmd_element_t *cmd)
{
	cmd_node_t *cnode;


	if (!cmdvec)
		return;

	cnode = vector_slot(cmdvec, ntype);

	if (cnode == NULL) {
		log_message(LOG_ERR, "Command node %d doesn't exist, please check it\n"
				   , ntype);
		exit(1);
	}

	vector_set(cnode->cmd_vector, cmd);

	if (cmd->strvec == NULL)
		cmd->strvec = cmd_make_descvec(cmd->string, cmd->doc);

	cmd->cmdsize = cmd_cmdsize(cmd->strvec);
}
