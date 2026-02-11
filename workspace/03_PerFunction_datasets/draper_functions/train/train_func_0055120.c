write_binding_scope(FILE *db_file, struct binding *bnd, char *prepend) {
	char *s;

	if ((db_file == NULL) || (bnd == NULL) || (prepend == NULL))
		return DHCP_R_INVALIDARG;

	if (bnd->value->type == binding_data) {
		if (bnd->value->value.data.data != NULL) {
			s = quotify_buf(bnd->value->value.data.data,
					bnd->value->value.data.len, MDL);
			if (s != NULL) {
				errno = 0;
				fprintf(db_file, "%sset %s = \"%s\";",
					prepend, bnd->name, s);
				if (errno)
					return ISC_R_FAILURE;

				dfree(s, MDL);
			} else {
			    return ISC_R_FAILURE;
			}
		}
	} else if (bnd->value->type == binding_numeric) {
		errno = 0;
		fprintf(db_file, "%sset %s = %%%ld;", prepend,
			bnd->name, bnd->value->value.intval);
		if (errno)
			return ISC_R_FAILURE;
	} else if (bnd->value->type == binding_boolean) {
		errno = 0;
		fprintf(db_file, "%sset %s = %s;", prepend, bnd->name,
			bnd->value->value.intval ? "true" : "false");
		if (errno)
			return ISC_R_FAILURE;
	} else if (bnd->value->type == binding_dns) {
		log_error("%s: persistent dns values not supported.",
			  bnd->name);
	} else if (bnd->value->type == binding_function) {
		log_error("%s: persistent functions not supported.",
			  bnd->name);
	} else {
		log_fatal("%s: unknown binding type %d", bnd->name,
			  bnd->value->type);
	}

	return ISC_R_SUCCESS;
}
