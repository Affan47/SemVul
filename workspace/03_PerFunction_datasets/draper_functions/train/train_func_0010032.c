_gmpi_parse_init_recv_msg(mpi_plugin_client_info_t *job, char *rbuf,
				     gm_slave_t *slave_data, int *ii)
{
	unsigned int magic, id, port_board_id, unique_high_id,
		unique_low_id, numanode, remote_pid, remote_port;
	int got;
	gm_slave_t *dp;

	got = sscanf(rbuf, "<<<%u:%u:%u:%u:%u:%u:%u::%u>>>",
		     &magic, &id, &port_board_id, &unique_high_id,
		     &unique_low_id, &numanode, &remote_pid, &remote_port);
	*ii = id;
	if (got != 8) {
		error("GMPI master received invalid init message");
		return -1;
	}
	if (magic != job->jobid) {
		error("GMPI master received invalid magic number");
		return -1;
	}
	if (id >= job->step_layout->task_cnt)
		fatal("GMPI id is out of range");
	if (port_board_id == 0)
		fatal("MPI id=%d was unable to open a GM port", id);

	dp = &slave_data[id];
	if (dp->defined) {
		error("Ignoring the message from MPI id=%d", id);
		return -1;
	}
	dp->defined = 1;
	dp->port_board_id = port_board_id;
	dp->unique_high_id = unique_high_id;
	dp->unique_low_id = unique_low_id;
	dp->numanode = numanode;
	dp->remote_pid = remote_pid;
	dp->remote_port = remote_port;

	debug3("slave_data[%d]: <<<%u:%u:%u:%u:%u:%u:%u::%u>>>",
	       id, magic, id, port_board_id,
	       dp->unique_high_id, dp->unique_low_id, dp->numanode,
	       dp->remote_pid, dp->remote_port);
	return 0;
}
