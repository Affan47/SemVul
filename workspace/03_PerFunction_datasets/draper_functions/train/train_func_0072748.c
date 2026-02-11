bfa_fcport_get_loop_attr(struct bfa_fcs_lport_s *port)
{
	int i = 0, j = 0, bit = 0, alpa_bit = 0;
	u8 k = 0;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(port->fcs->bfa);

	port->port_topo.ploop.alpabm_valid = fcport->alpabm_valid;
	port->pid = fcport->myalpa;
	port->pid = bfa_hton3b(port->pid);

	for (i = 0; i < (FC_ALPA_MAX / 8); i++) {
		for (j = 0, alpa_bit = 0; j < 8; j++, alpa_bit++) {
			bfa_trc(port->fcs->bfa, fcport->alpabm.alpa_bm[i]);
			bit = (fcport->alpabm.alpa_bm[i] & (1 << (7 - j)));
			if (bit) {
				port->port_topo.ploop.alpa_pos_map[k] =
					loop_alpa_map[(i * 8) + alpa_bit];
				k++;
				bfa_trc(port->fcs->bfa, k);
				bfa_trc(port->fcs->bfa,
					 port->port_topo.ploop.alpa_pos_map[k]);
			}
		}
	}
	port->port_topo.ploop.num_alpa = k;
}
