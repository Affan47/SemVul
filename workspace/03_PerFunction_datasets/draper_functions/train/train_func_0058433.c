agent_create_with_locker(Locker *locker)
{
	Agent *agent = mem_new(Agent);

	if (!agent)
		return NULL;

	memset(agent, 0, sizeof(Agent));

#ifdef HAVE_POLL
	agent->method = POLL;
#else
	agent->method = SELECT;
#endif

	agent->locker = locker;

	return agent;
}
