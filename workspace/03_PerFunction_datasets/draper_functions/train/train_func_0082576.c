proc_do(void)
{
	for (;;) {
		int pid;
		int status;
		unsigned int i;

		pid = waitpid(0, &status, WNOHANG);

		if (pid <= 0) {
			break;
		}

		for (i = 0; ; i++) {
			if (callback_count <= i) {

				break;
			}
			if (pid == callback[i].pid) {
				(*callback[i].f)(pid, callback[i].s);
				break;
			}
		}
	}
}
