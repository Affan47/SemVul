sim_ctl_set_issm(Client * cl, struct sim_ctl * ctl)
{
	int issm = *(int *)ctl->data;

	VERB("set issm %d port %" PRIx64, issm, cl->port->portguid);
	cl->issm = issm;
	set_issm(cl->port, issm);

	return 0;
}
