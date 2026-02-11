bfa_fcs_lport_ns_sm_offline(struct bfa_fcs_lport_ns_s *ns,
			enum vport_ns_event event)
{
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	switch (event) {
	case NSSM_EVENT_PORT_ONLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_plogi_sending);
		bfa_fcs_lport_ns_send_plogi(ns, NULL);
		break;

	case NSSM_EVENT_PORT_OFFLINE:
		break;

	default:
		bfa_sm_fault(ns->port->fcs, event);
	}
}
