setDirection(bool out)
{
	int datadir;

	D(bug("ParallelParport: setDirection"));
	if (handle<0) {
		return;
	}

	datadir = out ? 0 : 1;
	if (ioctl(handle, PPDATADIR, &datadir)<0) {
		panicbug("ParallelParport: Can not set direction");
	}
}
