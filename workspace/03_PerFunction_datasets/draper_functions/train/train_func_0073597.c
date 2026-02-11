configure(Vector<String> &conf, ErrorHandler *errh)
{
    _timeout = 0;
    _gc_interval = 20 * 60;

    if (Args(conf, this, errh)
	.read("TIMEOUT", SecondsArg(), _timeout)
	.read("REAP", SecondsArg(), _gc_interval)
	.complete() < 0)
	return -1;

    return 0;
}
