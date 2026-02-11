rb_set_time(void)
{
	struct timeval newtime;

	if(rb_unlikely(rb_gettimeofday(&newtime, NULL) == -1))
	{
		rb_lib_log("Clock Failure (%s)", strerror(errno));
		rb_lib_restart("Clock Failure");
	}

	if(newtime.tv_sec < rb_time.tv_sec)
		rb_set_back_events(rb_time.tv_sec - newtime.tv_sec);

	memcpy(&rb_time, &newtime, sizeof(struct timeval));
}
