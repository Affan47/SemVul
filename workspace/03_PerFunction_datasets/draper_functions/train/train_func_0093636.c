recvcommand(fd, commp, trp)
int fd;
command_t **commp;
syntaxtree *trp;
{
	command_t *comm;
	char **argv;
	int n;

	if (recvbuf(fd, &comm, sizeof(comm)) < 0) return(-1);

	if (comm) {
		if (trp -> flags & ST_NODE)
			return(recvstree(fd, (syntaxtree **)commp, trp));

		comm = (command_t *)Xmalloc(sizeof(command_t));
		if (recvbuf(fd, comm, sizeof(*comm)) < 0) {
			Xfree(comm);
			return(-1);
		}
		argv = comm -> argv;
		comm -> argv = NULL;
		comm -> redp = NULL;
		if (!argv) n = 0;
		else if (!isstatement(comm)) n = recvvar(fd, &(comm -> argv));
		else n = recvstree(fd, (syntaxtree **)&(comm -> argv), trp);
		if (n < 0 || recvrlist(fd, &(comm -> redp)) < 0) {
			freecomm(comm, 0);
			return(-1);
		}
	}
	*commp = comm;

	return(0);
}
