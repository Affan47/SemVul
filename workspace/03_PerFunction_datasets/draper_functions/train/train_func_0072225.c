_poll_for_all_vgs(struct cmd_context *cmd,
			      struct daemon_parms *parms)
{
	while (1) {
		parms->outstanding_count = 0;
		process_each_vg(cmd, 0, NULL, READ_FOR_UPDATE, parms, _poll_vg);
		if (!parms->outstanding_count)
			break;
		sleep(parms->interval);
	}
}
