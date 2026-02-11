installedTask()
{
	Task::installedTask();

	if (myserver->getfd() < 0)
	{
		serverResponse("OK");
		return;
	}

	myserver->socketWrite("QUIT\r\n");
}
