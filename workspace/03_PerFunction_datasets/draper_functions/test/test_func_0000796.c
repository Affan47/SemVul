readline(void)
{
        unsigned char buffer[128];
	char *p;
	int ret, i;

	ret = read(0, buffer, sizeof(buffer));
	if (ret == 0 || (ret == -1 && errno != EINTR)) {

		signal_emit("command quit", 1, "Lost terminal");
                return;
	}

	for (i = 0; i < ret; i++)
		g_string_append_c(input, buffer[i]);

	p = strchr(input->str, '\n');
	if (p != NULL) {
		*p = '\0';
		signal_emit("send command", 3, input->str,
			    active_win->active_server, active_win->active);
		*p = '\n';
		g_string_erase(input, 0, (int) (p-input->str)+1);
	}
}
