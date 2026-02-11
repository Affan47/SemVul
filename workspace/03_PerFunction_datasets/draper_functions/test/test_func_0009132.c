event_exit(int errcode)
{
	if (fatal_fn)
		fatal_fn(errcode);
	else if (errcode == _EVENT_ERR_ABORT)
		abort();
	else
		exit(errcode);
}
