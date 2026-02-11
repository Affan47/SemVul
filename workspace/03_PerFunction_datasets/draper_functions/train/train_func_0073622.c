_lldpctl_atom_free_port(lldpctl_atom_t *atom)
{
	struct _lldpctl_atom_port_t *port =
	    (struct _lldpctl_atom_port_t *)atom;
	struct lldpd_hardware *hardware = port->hardware;
	struct lldpd_chassis  *one_chassis, *one_chassis_next;
	struct lldpd_port     *one_port;


	struct chassis_list chassis_list;
	TAILQ_INIT(&chassis_list);

	if (port->parent) lldpctl_atom_dec_ref((lldpctl_atom_t*)port->parent);
	else if (!hardware) {


		lldpd_chassis_cleanup(port->port->p_chassis, 1);
		port->port->p_chassis = NULL;
		lldpd_port_cleanup(port->port, 1);
		free(port->port);
	}
	if (!hardware) return;

	add_chassis(&chassis_list, port->port->p_chassis);
	TAILQ_FOREACH(one_port, &hardware->h_rports, p_entries)
		add_chassis(&chassis_list, one_port->p_chassis);


	lldpd_remote_cleanup(hardware, NULL, 1);
	lldpd_port_cleanup(port->port, 1);
	free(port->hardware);


	for (one_chassis = TAILQ_FIRST(&chassis_list);
	     one_chassis != NULL;
	     one_chassis = one_chassis_next) {
		one_chassis_next = TAILQ_NEXT(one_chassis, c_entries);
		lldpd_chassis_cleanup(one_chassis, 1);
	}
}
