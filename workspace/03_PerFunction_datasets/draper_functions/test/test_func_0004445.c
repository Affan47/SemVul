name_from_idn(const char *idn_name) {
#ifdef LIBIDN
	char *name = NULL;

	int rc = idna_to_ascii_lz(idn_name, &name, 0);
	if (rc != IDNA_SUCCESS) {
		ERR("IDNA (%s)\n", idna_strerror(rc));
		return NULL;
	}

	return name;
#endif
	return strdup(idn_name);
}
