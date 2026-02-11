evemu_play_one(int fd, const struct input_event *ev)
{
	int ret;
	SYSCALL(ret = write(fd, ev, sizeof(*ev)));
	return (ret < sizeof(*ev));
}
