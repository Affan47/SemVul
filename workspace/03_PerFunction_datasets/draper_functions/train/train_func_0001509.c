PostmasterIsAlive(bool amDirectChild)
{
#ifndef WIN32
	if (amDirectChild)
	{
		pid_t		ppid = getppid();


		if (ppid == PostmasterPid)
			return true;


		if (ppid == 1)
			return false;


	}


	return (kill(PostmasterPid, 0) == 0);
#else
	return (WaitForSingleObject(PostmasterHandle, 0) == WAIT_TIMEOUT);
#endif
}
