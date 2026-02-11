reopen_listeners(void)
{
	aClient *acptr;
	aConfItem *aconf;
	for (acptr = ListenerLL; acptr; acptr = acptr->next)
	{
		aconf = acptr->confs->value.aconf;
		if (!IsIllegal(aconf) && acptr->fd < 0)
		{
			open_listener(acptr);
		}
	}
}
