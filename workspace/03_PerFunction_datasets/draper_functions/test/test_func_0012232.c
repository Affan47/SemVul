printcmsghdr(struct tcb *tcp, unsigned long addr, unsigned long len)
{
	struct cmsghdr *cmsg = len < sizeof(struct cmsghdr) ?
			       NULL : malloc(len);
	if (cmsg == NULL || umoven(tcp, addr, len, (char *) cmsg) < 0) {
		tprintf(", msg_control=%#lx", addr);
		free(cmsg);
		return;
	}

	tprintf(", {cmsg_len=%u, cmsg_level=", (unsigned) cmsg->cmsg_len);
	printxval(socketlayers, cmsg->cmsg_level, "SOL_???");
	tprintf(", cmsg_type=");

	if (cmsg->cmsg_level == SOL_SOCKET) {
		unsigned long cmsg_len;

		printxval(scmvals, cmsg->cmsg_type, "SCM_???");
		cmsg_len = (len < cmsg->cmsg_len) ? len : cmsg->cmsg_len;

		if (cmsg->cmsg_type == SCM_RIGHTS
		    && CMSG_LEN(sizeof(int)) <= cmsg_len) {
			int *fds = (int *) CMSG_DATA (cmsg);
			int first = 1;

			tprintf(", {");
			while ((char *) fds < ((char *) cmsg + cmsg_len)) {
				if (!first)
					tprintf(", ");
				tprintf("%d", *fds++);
				first = 0;
			}
			tprintf("}}");
			free(cmsg);
			return;
		}
		if (cmsg->cmsg_type == SCM_CREDENTIALS
		    && CMSG_LEN(sizeof(struct ucred)) <= cmsg_len) {
			struct ucred *uc = (struct ucred *) CMSG_DATA (cmsg);

			tprintf("{pid=%ld, uid=%ld, gid=%ld}}",
				(long)uc->pid, (long)uc->uid, (long)uc->gid);
			free(cmsg);
			return;
		}
	}
	free(cmsg);
	tprintf(", ...}");
}
