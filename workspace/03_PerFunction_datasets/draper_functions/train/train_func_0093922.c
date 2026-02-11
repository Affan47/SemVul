net_connect_job_stop(struct net_connect_job* job)
{
	if (job->addr.ss_family == AF_INET6)
	{
		job->handle->job6 = job->next;
	}
	else
	{
		job->handle->job4 = job->next;
	}

	net_connect_job_free(job);
}
