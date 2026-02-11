wait(int timeout)
{
	if (triggers.empty())
	{
		CL_System::sleep(timeout);
		return false;
	}

	fd_set rfds;
	FD_ZERO(&rfds);
	int highest_fd = -1;

	std::list< CL_SharedPtr<CL_EventTrigger_Generic> >::iterator it;
	for (it = triggers.begin(); it != triggers.end(); ++it)
	{
		CL_EventTrigger_Unix *trigger = static_cast<CL_EventTrigger_Unix*>((*it).get());

		if (trigger->wait_pipe[0] > highest_fd) highest_fd = trigger->wait_pipe[0];
		FD_SET(trigger->wait_pipe[0], &rfds);
	}

	timeval tv;
	tv.tv_sec = timeout/1000;
	tv.tv_usec = (timeout%1000)*1000;

	int result = select(
		highest_fd+1,
		&rfds,
		NULL,
		NULL,
		(timeout == -1) ? NULL : &tv);

	if (result <= 0) return false;
	return true;
}
