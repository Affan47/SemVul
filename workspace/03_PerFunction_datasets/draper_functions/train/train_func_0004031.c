gres_plugin_help_msg(char *msg, int msg_size)
{
	int i, rc;
	char *header = "Valid gres options are:\n";

	if (msg_size < 1)
		return EINVAL;

	msg[0] = '\0';
	rc = gres_plugin_init();

	if ((strlen(header) + 2) <= msg_size)
		strcat(msg, header);
	slurm_mutex_lock(&gres_context_lock);
	for (i=0; ((i < gres_context_cnt) && (rc == SLURM_SUCCESS)); i++) {
		if ((strlen(msg) + strlen(gres_context[i].gres_name) + 9) >
		    msg_size)
 			break;
		strcat(msg, gres_context[i].gres_name);
		strcat(msg, "[:count]\n");
	}
	slurm_mutex_unlock(&gres_context_lock);

	return rc;
}
