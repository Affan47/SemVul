ldns_str2rdf_ilnp64(ldns_rdf **rd, const char *str)
{
	unsigned int a, b, c, d;
	uint16_t shorts[4];
	int l;

	if (sscanf(str, "%4x:%4x:%4x:%4x%n", &a, &b, &c, &d, &l) != 4 ||
			l != (int)strlen(str) ||
			strpbrk(str, "+-")
			) {
		return LDNS_STATUS_INVALID_ILNP64;
	} else {
		shorts[0] = htons(a);
		shorts[1] = htons(b);
		shorts[2] = htons(c);
		shorts[3] = htons(d);
		*rd = ldns_rdf_new_frm_data(
			LDNS_RDF_TYPE_ILNP64, 4 * sizeof(uint16_t), &shorts);
	}
	return *rd ? LDNS_STATUS_OK : LDNS_STATUS_MEM_ERR;
}
