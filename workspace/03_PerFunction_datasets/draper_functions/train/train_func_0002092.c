g2_packet_decide_spec(struct ptype_action_args *parg, g2_ptype_action_func const *work_type)
{
	uint8_t *guid;

	if(g2_packet_needs_routing(parg->source, &guid))
		return magic_route(parg, guid);

	return g2_packet_decide_spec_int(parg, work_type);
}
