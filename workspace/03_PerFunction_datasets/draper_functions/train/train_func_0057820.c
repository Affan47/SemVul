keep_alive()
{
	struct js_event event;

	while (read(fd, &event, sizeof(struct js_event)) != -1)
	{
		process_event(event);
	}

	if (errno != EAGAIN) {
		throw CL_Error(strerror(errno));
	}
}
