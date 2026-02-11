Reconnect
	(
	gpointer data
	)
	{
	ExultStudio *studio = (ExultStudio *) data;
	if (studio->connect_to_server())
		return 0;
	else
		return 1;
	}
