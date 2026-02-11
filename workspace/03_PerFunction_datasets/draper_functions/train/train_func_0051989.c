rms_rewind(RMSHANDLE h, struct RAB *rab)
{
    if (!h) return -1;

    rms_conn *rc = (rms_conn *)h;
    dap_connection *conn = (dap_connection *)rc->conn;

    dap_control_message ctl;
    ctl.set_ctlfunc(dap_control_message::REWIND);

    if (rab) build_control_message(rc,&ctl, rab);

    if (!ctl.write(*conn))
    {
	rc->lasterror = conn->get_error();
	return -1;
    }

    dap_message *m;
    int r = rms_getreply(h, 1, NULL, &m);
    if (r == -2) delete m;
    if (r < 0) return -1;

    return 0;
}
