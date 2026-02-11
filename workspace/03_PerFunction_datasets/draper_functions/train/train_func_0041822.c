lldpd_update_localports(struct lldpd *cfg)
{
	struct lldpd_hardware *hardware;

	log_debug("localchassis", "update information for local ports");


	TAILQ_FOREACH(hardware, &cfg->g_hardware, h_entries)
	    hardware->h_flags = 0;

	TRACE(LLDPD_INTERFACES_UPDATE());
	interfaces_update(cfg);
	lldpd_cleanup(cfg);
	lldpd_reset_timer(cfg);
}
