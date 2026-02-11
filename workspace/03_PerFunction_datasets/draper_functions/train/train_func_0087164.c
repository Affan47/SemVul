ndmda_data_start_backup (struct ndm_session *sess)
{
	struct ndm_data_agent *	da = &sess->data_acb;
	ndmp9_error		error = NDMP9_NO_ERR;
	char			cmd[NDMDA_MAX_CMD];

	strcpy (cmd, "wrap_");
	strcat (cmd, da->bu_type);

	if (sess->param.log_level > 0) {
	    char tmpbuf[40];
	    sprintf(tmpbuf, "-d%d", sess->param.log_level);
	    ndmda_add_to_cmd (cmd, tmpbuf);
	}

	ndmda_add_to_cmd (cmd, "-c");
	ndmda_add_to_cmd (cmd, "-I#3");
	add_env (&da->env_tab, cmd);

	ndma_send_logmsg (sess, NDMP9_LOG_DEBUG, sess->plumb.data,
		"CMD: %s", cmd);

	if (ndmda_pipe_fork_exec (sess, cmd, 1) < 0) {
		return NDMP9_UNDEFINED_ERR;
	}

	ndmis_data_start (sess, NDMCHAN_MODE_WRITE);

	da->data_state.state = NDMP9_DATA_STATE_ACTIVE;
	da->data_state.operation = NDMP9_DATA_OP_BACKUP;

	return error;
}
