net_connect_job_process(struct net_connect_job* job)
{
	int sd;
	if (!job->con)
	{
		sd = net_socket_create(job->addr.ss_family, SOCK_STREAM, IPPROTO_TCP);
		if (sd == -1)
		{
			LOG_DEBUG("net_connect_job_process: Unable to create socket!");
			net_connect_callback(job->handle, net_connect_status_socket_error, NULL);
			return -1;
		}

		job->con = 	net_con_create();
		net_con_initialize(job->con, sd, net_connect_job_internal_cb, job, NET_EVENT_WRITE);
		net_con_set_timeout(job->con, TIMEOUT_CONNECTED);
	}

	return net_connect_job_check(job);
}
