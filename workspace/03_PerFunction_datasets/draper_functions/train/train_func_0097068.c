idbm_discovery_write(discovery_rec_t *rec)
{
	FILE *f;
	char *portal;
	int rc = 0;

	if (rec->type > 1)
		return ISCSI_ERR_INVAL;

	portal = malloc(PATH_MAX);
	if (!portal) {
		log_error("Could not alloc portal");
		return ISCSI_ERR_NOMEM;
	}

	rc = idbm_lock();
	if (rc)
		goto free_portal;

	snprintf(portal, PATH_MAX, "%s",
		 disc_type_to_config_vals[rec->type].config_root);
	if (access(portal, F_OK) != 0) {
		if (mkdir(portal, 0660) != 0) {
			log_error("Could not make %s: %s", portal,
				  strerror(errno));
			rc = ISCSI_ERR_IDBM;
			goto unlock;
		}
	}

	snprintf(portal, PATH_MAX, "%s/%s,%d",
		 disc_type_to_config_vals[rec->type].config_root,
		 rec->address, rec->port);

	f = idbm_open_rec_w(portal,
			    disc_type_to_config_vals[rec->type].config_name);
	if (!f) {
		log_error("Could not open %s: %s", portal, strerror(errno));
		rc = ISCSI_ERR_IDBM;
		goto unlock;
	}

	idbm_print(IDBM_PRINT_TYPE_DISCOVERY, rec, 1, f);
	fclose(f);
unlock:
	idbm_unlock();
free_portal:
	free(portal);
	return rc;
}
