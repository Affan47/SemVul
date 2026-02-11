set_filters(int u, struct bpf_program *pass, struct bpf_program *active)
{
        struct sock_fprog fp;


	if (pass) {
		fp.len = pass->bf_len;
		fp.filter = (struct sock_filter *) pass->bf_insns;
		if (ioctl(lns[u].fd, PPPIOCSPASS, &fp) < 0) {
			syslog(LOG_ERR, "Couldn't set pass-filter in kernel.");
			return 0;
		}
	}
	if (active) {
		fp.len = active->bf_len;
		fp.filter = (struct sock_filter *) active->bf_insns;
		if (ioctl(lns[u].fd, PPPIOCSACTIVE, &fp) < 0) {
			syslog(LOG_ERR, "Couldn't set active-filter in kernel.");
	        	return 0;
		}
	}
	return 1;
}
