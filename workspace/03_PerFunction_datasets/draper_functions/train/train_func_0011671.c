iasubopt_reference(struct iasubopt **iasubopt, struct iasubopt *src,
		 const char *file, int line) {
	if (iasubopt == NULL) {
		log_error("%s(%d): NULL pointer reference", file, line);
		return DHCP_R_INVALIDARG;
	}
	if (*iasubopt != NULL) {
		log_error("%s(%d): non-NULL pointer", file, line);
		return DHCP_R_INVALIDARG;
	}
	if (src == NULL) {
		log_error("%s(%d): NULL pointer reference", file, line);
		return DHCP_R_INVALIDARG;
	}
	*iasubopt = src;
	src->refcnt++;
	return ISC_R_SUCCESS;
}
