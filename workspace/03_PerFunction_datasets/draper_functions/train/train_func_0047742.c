is_active()
{
    if (imonfd == -2)
    {   imonfd = imon_open();
	if (imonfd >= 0)
	{   Log::debug("opened /dev/imon");
	    (void) Scheduler::install_read_handler(imonfd, read_handler, NULL);
	}
    }
    return imonfd >= 0;
}
