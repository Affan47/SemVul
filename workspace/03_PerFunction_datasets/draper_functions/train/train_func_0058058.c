serverToggle(bool switchOn)
{
	if (switchOn && (!serverRunning))
		startServer();
	else if ((!switchOn) && serverRunning)
		stopServer();
}
