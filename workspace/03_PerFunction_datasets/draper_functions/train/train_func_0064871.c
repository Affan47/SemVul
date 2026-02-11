bfa_fcs_lport_get_rport_max_speed(bfa_fcs_lport_t *port)
{
	struct list_head *qh, *qe;
	struct bfa_fcs_rport_s *rport = NULL;
	struct bfa_fcs_s	*fcs;
	bfa_port_speed_t max_speed = 0;
	struct bfa_port_attr_s port_attr;
	bfa_port_speed_t port_speed, rport_speed;
	bfa_boolean_t trl_enabled = bfa_fcport_is_ratelim(port->fcs->bfa);


	if (port == NULL)
		return 0;

	fcs = port->fcs;


	bfa_fcport_get_attr(port->fcs->bfa, &port_attr);
	port_speed = port_attr.speed;
	bfa_trc(fcs, port_speed);

	qh = &port->rport_q;
	qe = bfa_q_first(qh);

	while (qe != qh) {
		rport = (struct bfa_fcs_rport_s *) qe;
		if ((bfa_ntoh3b(rport->pid) > 0xFFF000) ||
			(bfa_fcs_rport_get_state(rport) == BFA_RPORT_OFFLINE) ||
			(rport->scsi_function != BFA_RPORT_TARGET)) {
			qe = bfa_q_next(qe);
			continue;
		}

		rport_speed = rport->rpf.rpsc_speed;
		if ((trl_enabled) && (rport_speed ==
			BFA_PORT_SPEED_UNKNOWN)) {

			rport_speed =
				bfa_fcport_get_ratelim_speed(port->fcs->bfa);
		}

		if (rport_speed > max_speed)
			max_speed = rport_speed;

		qe = bfa_q_next(qe);
	}

	if (max_speed > port_speed)
		max_speed = port_speed;

	bfa_trc(fcs, max_speed);
	return max_speed;
}
