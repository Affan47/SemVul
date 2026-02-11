enter()
{
	debug_log("entering dispatcher %p", this);

	_running = true;

	while (_running)
	{
		do_iteration();
	}

	debug_log("leaving dispatcher %p", this);
}
