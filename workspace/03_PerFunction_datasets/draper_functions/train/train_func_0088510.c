helperStatefulShutdown(statefulhelper * hlp)
{
    dlink_node *link = hlp->servers.head;
    helper_stateful_server *srv;
#ifdef _SQUID_MSWIN_
    HANDLE hIpc;
    pid_t pid;
    int no;
#endif
    int wfd;
    while (link) {
	srv = link->data;
	link = link->next;
	if (srv->flags.shutdown) {
	    debug(84, 3) ("helperStatefulShutdown: %s #%d is already shut down.\n",
		hlp->id_name, srv->index + 1);
	    continue;
	}
	hlp->n_active--;
	assert(hlp->n_active >= 0);
	srv->flags.shutdown = 1;
	if (srv->flags.busy) {
	    debug(84, 3) ("helperStatefulShutdown: %s #%d is BUSY.\n",
		hlp->id_name, srv->index + 1);
	    continue;
	}
	if (srv->flags.closing) {
	    debug(84, 3) ("helperStatefulShutdown: %s #%d is CLOSING.\n",
		hlp->id_name, srv->index + 1);
	    continue;
	}
	if (srv->flags.reserved) {
	    debug(84, 3) ("helperStatefulShutdown: %s #%d is RESERVED.\n",
		hlp->id_name, srv->index + 1);
	    continue;
	}
	srv->flags.closing = 1;
#ifdef _SQUID_MSWIN_
	hIpc = srv->hIpc;
	pid = srv->pid;
	no = srv->index + 1;
	shutdown(srv->wfd, SD_BOTH);
#endif
	wfd = srv->wfd;
	srv->wfd = -1;
	comm_close(wfd);
#ifdef _SQUID_MSWIN_
	if (hIpc) {
	    if (WaitForSingleObject(hIpc, 5000) != WAIT_OBJECT_0) {
		getCurrentTime();
		debug(84, 1) ("helperStatefulShutdown: WARNING: %s #%d (%s,%ld) "
		    "didn't exit in 5 seconds\n",
		    hlp->id_name, no, hlp->cmdline->key, (long int) pid);
	    }
	    CloseHandle(hIpc);
	}
#endif
    }
}
