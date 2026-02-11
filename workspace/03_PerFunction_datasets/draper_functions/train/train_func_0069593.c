unix_cmd(dst_work *work)
{
	static int cmd_index = 0;
	int cnt = 0, n;
	FILE *pipe;
	u_char buffer[4096];

	if (cmds[cmd_index] == NULL)
		cmd_index = 0;
	EREPORT(("unix_cmd() i %d filled %4d in_temp %4d\n",
		 cmd_index, work->filled, work->in_temp));
	pipe = popen(cmds[cmd_index++], "r");

	while ((n = fread(buffer, sizeof(char), sizeof(buffer), pipe)) > 0) {
		cnt += n;
		if (my_digest(work, buffer, (unsigned)n))
			break;

		cnt += do_time(work);
	}
	while ((n = fread(buffer, sizeof(char), sizeof(buffer), pipe)) > 0)
		;
	pclose(pipe);
	return (cnt);
}
