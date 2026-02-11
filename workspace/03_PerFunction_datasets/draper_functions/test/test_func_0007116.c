setBaudRate(BaudRate r)
{
    if (server.setBaudRate(r)) {
	if (conf.baudRateDelay)
	    pause(conf.baudRateDelay);
	return (true);
    } else
	return (false);
}
