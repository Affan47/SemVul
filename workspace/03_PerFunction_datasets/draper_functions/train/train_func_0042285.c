cmd_iface_promisc(struct lldpctl_conn_t *conn, struct writer *w,
    struct cmd_env *env, void *arg)
{
	lldpctl_atom_t *config = lldpctl_get_configuration(conn);
	if (config == NULL) {
		log_warnx("lldpctl", "unable to get configuration from lldpd. %s",
		    lldpctl_last_strerror(conn));
		return 0;
	}
	if (lldpctl_atom_set_int(config,
		lldpctl_k_config_iface_promisc,
		arg?1:0) == NULL) {
		log_warnx("lldpctl", "unable to %s promiscuous mode: %s",
		    arg?"enable":"disable",
		    lldpctl_last_strerror(conn));
		lldpctl_atom_dec_ref(config);
		return 0;
	}
	log_info("lldpctl", "interface promiscuous mode %s",
	    arg?"enabled":"disabled");
	lldpctl_atom_dec_ref(config);
	return 1;
}
