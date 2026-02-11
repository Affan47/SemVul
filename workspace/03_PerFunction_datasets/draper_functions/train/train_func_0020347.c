helperStatefulDispatch(helper_stateful_server * srv, helper_stateful_request * r)
{
    statefulhelper *hlp = srv->parent;
    if (!cbdataValid(r->data)) {
	debug(84, 1) ("helperStatefulDispatch: invalid callback data\n");
	helperStatefulRequestFree(r);
	return;
    }
    if (!r->buf) {
	if (cbdataValid(r->data)) {
	    r->callback(r->data, srv, NULL);
	} else {
	    debug(84, 1) ("helperStatefulDispatch: no callback data registered\n");
	}
	helperStatefulRequestFree(r);
	return;
    }
    debug(84, 9) ("helperStatefulDispatch busying helper %s #%d\n", hlp->id_name, srv->index + 1);
    srv->flags.busy = 1;
    srv->request = r;
    srv->dispatch_time = current_time;
    comm_write(srv->wfd,
	r->buf,
	strlen(r->buf),
	NULL,
	NULL,
	NULL);
    debug(84, 5) ("helperStatefulDispatch: Request sent to %s #%d, %d bytes\n",
	hlp->id_name, srv->index + 1, (int) strlen(r->buf));
    srv->stats.uses++;
    hlp->stats.requests++;
}
