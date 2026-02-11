_spawn_signal_thread(uint64_t cont_id, int signal)
{
	agent_arg_t *agent_arg_ptr;
	pthread_attr_t attr_agent;
	pthread_t thread_agent;

	slurm_attr_init(&attr_agent);
	if (pthread_attr_setdetachstate(&attr_agent, PTHREAD_CREATE_DETACHED))
		error("pthread_attr_setdetachstate error %m");
	agent_arg_ptr = xmalloc(sizeof(agent_arg_t));
	agent_arg_ptr->cont_id = cont_id;
	agent_arg_ptr->signal  = signal;
	(void) pthread_create(&thread_agent, &attr_agent,
			     _sig_agent, (void *) agent_arg_ptr);
	slurm_attr_destroy(&attr_agent);
}
