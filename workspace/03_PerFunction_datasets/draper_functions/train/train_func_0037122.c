cmd_watch_neighbors(struct lldpctl_conn_t *conn, struct writer *w,
    struct cmd_env *env, void *arg)
{
	int watch = 1;
	struct watcharg wa = {
		.env = env,
		.w = w
	};
	log_debug("lldpctl", "watch for neighbor changes");
	if (lldpctl_watch_callback(conn, watchcb, &wa) < 0) {
		log_warnx("lldpctl", "unable to watch for neighbors. %s",
		    lldpctl_last_strerror(conn));
		return 0;
	}
	while (watch) {
		if (lldpctl_watch(conn) < 0) {
			log_warnx("lldpctl", "unable to watch for neighbors. %s",
			    lldpctl_last_strerror(conn));
			watch = 0;
		}
	}
	return 0;
}
