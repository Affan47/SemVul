bfa_trunk_iocdisable(struct bfa_s *bfa)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	int i = 0;


	if (fcport->cfg.trunked) {
		if (fcport->trunk.attr.state == BFA_TRUNK_ONLINE)
			bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_TRUE);

		fcport->trunk.attr.state = BFA_TRUNK_OFFLINE;
		fcport->trunk.attr.speed = BFA_PORT_SPEED_UNKNOWN;
		for (i = 0; i < BFA_TRUNK_MAX_PORTS; i++) {
			fcport->trunk.attr.link_attr[i].trunk_wwn = 0;
			fcport->trunk.attr.link_attr[i].fctl =
						BFA_TRUNK_LINK_FCTL_NORMAL;
			fcport->trunk.attr.link_attr[i].link_state =
						BFA_TRUNK_LINK_STATE_DN_LINKDN;
			fcport->trunk.attr.link_attr[i].speed =
						BFA_PORT_SPEED_UNKNOWN;
			fcport->trunk.attr.link_attr[i].deskew = 0;
		}
	}
}
