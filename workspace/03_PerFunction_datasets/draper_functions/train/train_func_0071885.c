cs3_load(cs3_t * s)
{
	SANE_Status status;

	DBG(6, "%s\n", __func__);

	cs3_scanner_ready(s, CS3_STATUS_NO_DOCS);
	cs3_init_buffer(s);
	cs3_parse_cmd(s, "e0 00 d1 00 00 00 00 00 0d 00");
	s->n_send += 13;

	status = cs3_grow_send_buffer(s);
	if (status != SANE_STATUS_GOOD)
		return status;

	return cs3_issue_and_execute(s);
}
