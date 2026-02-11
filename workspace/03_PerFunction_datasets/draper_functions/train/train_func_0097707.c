dap_get_record(char *rec, int reclen)
{
    if (verbose > 2) DAPLOG((LOG_INFO, "in dap_get_record()\n"));

    dap_message *m = dap_message::read_message(conn,true);
    if (m)
    {
	if (m->get_type() == dap_message::STATUS)
	{
	    dap_status_message *sm = (dap_status_message *)m;
	    if ( (sm->get_code() & 0xFF) == 047)
	    {
		ateof = TRUE;
		return -1;
	    }

	    if (dap_check_status(m, 0) == 0)
		dap_send_get_or_put();
	    return dap_check_status(m,0);
	}

	if (m->get_type() == dap_message::ACK)
	{
	    return 0;
	}

	if (m->get_type() != dap_message::DATA)
	{
	    sprintf(errstring, "Wrong block type (%s) received", m->type_name());
	    lasterror = errstring;
	    return -1;
	}
	dap_data_message *dm = (dap_data_message *)m;
	unsigned int len = dm->get_datalen();
	rec[len] = 0;
	memcpy(rec, dm->get_dataptr(), len);

	return len;
    }
    lasterror = conn.get_error();
    return -1;
}
