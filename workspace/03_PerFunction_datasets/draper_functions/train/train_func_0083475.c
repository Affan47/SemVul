idbm_verify_param(recinfo_t *info, char *name)
{
	int i;

	for (i = 0; i < MAX_KEYS; i++) {
		if (strcmp(name, info[i].name))
			continue;

		log_debug(7, "verify %s %d\n", name, info[i].can_modify);
		if (info[i].can_modify)
			return 0;
		else {
			log_error("Cannot modify %s. It is used to look up "
				  "the record and cannot be changed.", name);
			return ISCSI_ERR_INVAL;
		}
	}

	log_error("Cannot modify %s. Invalid param name.", name);
	return ISCSI_ERR_INVAL;
}
