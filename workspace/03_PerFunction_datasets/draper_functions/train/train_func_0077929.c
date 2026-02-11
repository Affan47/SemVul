evemu_echo_event(FILE *fp)
{
	struct input_event ev;
	int ret;

	while ((ret = evemu_read_event(fp, &ev)) > 0)
		evemu_write_event(stdout, &ev);

	return ret;
}
