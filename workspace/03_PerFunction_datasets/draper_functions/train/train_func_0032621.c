slurm_free_kill_job_msg(kill_job_msg_t * msg)
{
	if (msg) {
		int i;
		xfree(msg->nodes);
		select_g_select_jobinfo_free(msg->select_jobinfo);
		msg->select_jobinfo = NULL;

		for (i=0; i<msg->spank_job_env_size; i++)
			xfree(msg->spank_job_env[i]);
		xfree(msg->spank_job_env);
		xfree(msg);
	}
}
