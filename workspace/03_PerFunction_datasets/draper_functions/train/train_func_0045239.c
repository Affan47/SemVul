lldpd_chassis_mgmt_cleanup(struct lldpd_chassis *chassis)
{
	struct lldpd_mgmt *mgmt, *mgmt_next;

	log_debug("alloc", "cleanup management addresses for chassis %s",
	    chassis->c_name ? chassis->c_name : "(unknown)");

	for (mgmt = TAILQ_FIRST(&chassis->c_mgmt);
	     mgmt != NULL;
	     mgmt = mgmt_next) {
		mgmt_next = TAILQ_NEXT(mgmt, m_entries);
		free(mgmt);
	}
	TAILQ_INIT(&chassis->c_mgmt);
}
