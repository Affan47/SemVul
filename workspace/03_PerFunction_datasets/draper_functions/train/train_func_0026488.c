ia_dereference(struct ia_xx **ia, const char *file, int line) {
	struct ia_xx *tmp;
	int i;

	if ((ia == NULL) || (*ia == NULL)) {
		log_error("%s(%d): NULL pointer", file, line);
		return DHCP_R_INVALIDARG;
	}

	tmp = *ia;
	*ia = NULL;

	tmp->refcnt--;
	if (tmp->refcnt < 0) {
		log_error("%s(%d): negative refcnt", file, line);
		tmp->refcnt = 0;
	}
	if (tmp->refcnt == 0) {
		if (tmp->iasubopt != NULL) {
			for (i=0; i<tmp->num_iasubopt; i++) {
				iasubopt_dereference(&(tmp->iasubopt[i]),
						     file, line);
			}
			dfree(tmp->iasubopt, file, line);
		}
		data_string_forget(&(tmp->iaid_duid), file, line);
		dfree(tmp, file, line);
	}
	return ISC_R_SUCCESS;
}
