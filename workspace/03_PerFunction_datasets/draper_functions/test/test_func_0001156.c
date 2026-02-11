remote_netdump_init(void)
{
        char sendbuf[BUFSIZE];
        char recvbuf[BUFSIZE];
        char *p1, *p2;
	ulong panic_task;

        BZERO(sendbuf, BUFSIZE);
        BZERO(recvbuf, BUFSIZE);
        sprintf(sendbuf, "NETDUMP_INIT %d %s", pc->rmfd, pc->server_memsrc);
        send(pc->sockfd, sendbuf, strlen(sendbuf), 0);
        recv(pc->sockfd, recvbuf, BUFSIZE-1, 0);
        if (strstr(recvbuf, "<FAIL>"))
                return FALSE;

        p1 = strstr(recvbuf, "panic_task: ");

        if (p1) {
                p1 += strlen("panic_task: ");
                p2 = strstr(p1, "\n");
                *p2 = NULLCHAR;
                panic_task = htol(p1, FAULT_ON_ERROR, NULL);
		tt->panic_task = panic_task;
                if (CRASHDEBUG(1))
                        fprintf(fp, "panic_task: %lx\n", tt->panic_task);
        }

        return TRUE;
}
