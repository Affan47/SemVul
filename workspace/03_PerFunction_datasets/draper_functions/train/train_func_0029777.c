bfa_fcport_is_linkup(struct bfa_s *bfa)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	return	(!fcport->cfg.trunked &&
		 bfa_sm_cmp_state(fcport, bfa_fcport_sm_linkup)) ||
		(fcport->cfg.trunked &&
		 fcport->trunk.attr.state == BFA_TRUNK_ONLINE);
}
