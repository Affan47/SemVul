idbm_create_rec(char *targetname, int tpgt, char *ip,
				 int port, struct iface_rec *iface,
				 int verbose)
{
	struct node_rec *rec;

	rec = calloc(1, sizeof(*rec));
	if (!rec) {
		log_error("Could not not allocate memory to create node "
			  "record.");
		return NULL;
	}

	idbm_node_setup_defaults(rec);
	if (targetname)
		strlcpy(rec->name, targetname, TARGET_NAME_MAXLEN);
	rec->tpgt = tpgt;
	rec->conn[0].port = port;
	if (ip)
		strlcpy(rec->conn[0].address, ip, NI_MAXHOST);
	memset(&rec->iface, 0, sizeof(struct iface_rec));
	if (iface) {
		iface_copy(&rec->iface, iface);
		if (strlen(iface->name)) {
			if (iface_conf_read(&rec->iface)) {
				if (verbose)
					log_error("Could not read iface info "
						  "for %s.", iface->name);
				goto free_rec;
			}
		}
	}
	return rec;
free_rec:
	free(rec);
	return NULL;
}
