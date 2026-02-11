getTimeout()
{
	time_t now;

	time(&now);

	if (now < defaultTimeout)
		return defaultTimeout - now;

	string errmsg=myserver->socketDisconnect();

	if (errmsg.size() == 0)
		errmsg="Server timed out.";

	disconnected(errmsg.c_str());
	return 0;
}
