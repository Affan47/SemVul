libwrap_ask(struct request_info *r, int fd)
{
    int a;
    struct sockaddr_storage sin;
    socklen_t len = sizeof(sin);


    sin.ss_family = AF_UNIX;


    if (getpeername(fd, (struct sockaddr *) &sin, &len) == 0) {
	if (((struct sockaddr *)&sin)->sa_family == AF_UNIX) {
	    return 1;
	}
    }


    request_set(r, RQ_FILE, fd, 0);
    sock_host(r);

    a = hosts_access(r);
    if (!a) {
	syslog(deny_severity, "refused connection from %s", eval_client(r));
    }

    return a;
}
