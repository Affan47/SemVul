iasubopt_dereference(struct iasubopt **iasubopt, const char *file, int line) {
	struct iasubopt *tmp;

	if ((iasubopt == NULL) || (*iasubopt == NULL)) {
		log_error("%s(%d): NULL pointer", file, line);
		return DHCP_R_INVALIDARG;
	}

	tmp = *iasubopt;
	*iasubopt = NULL;

	tmp->refcnt--;
	if (tmp->refcnt < 0) {
		log_error("%s(%d): negative refcnt", file, line);
		tmp->refcnt = 0;
	}
	if (tmp->refcnt == 0) {
		if (tmp->ia != NULL) {
			ia_dereference(&(tmp->ia), file, line);
		}
		if (tmp->ipv6_pool != NULL) {
			ipv6_pool_dereference(&(tmp->ipv6_pool), file, line);
		}
		if (tmp->scope != NULL) {
			binding_scope_dereference(&tmp->scope, file, line);
		}
		dfree(tmp, file, line);
	}

	return ISC_R_SUCCESS;
}
