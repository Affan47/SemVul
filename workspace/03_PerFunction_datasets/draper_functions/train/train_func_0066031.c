sigchld_handler(int signal)
{
	pid_t pid;
	int status;


	if ((pid = wait(&status)) != -1) {
		ProcInfo *p;


		for (p = proc_queue; p != NULL; p = p->next) {
			if (p->pid == pid) {
				p->status = status;
				p->endtime = time(NULL);
			}
		}
	}
}
