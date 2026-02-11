handle_PI_RELAY(struct ptype_action_args *parg)
{
	struct PI_data *rdata = parg->opaque;

	logg_packet_old(STDSF, "/PI/RELAY");
	rdata->relay = true;
	return false;
}
