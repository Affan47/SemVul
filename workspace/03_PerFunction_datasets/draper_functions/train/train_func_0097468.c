validate_rename(tentry *clean, tentry *data, int *deleteoldrdn)
{
	if (!*entry_dn(clean)) {
		puts("Error: Cannot rename ROOT_DSE.");
		return -1;
	}
	if (!*entry_dn(data)) {
		puts("Error: Cannot replace ROOT_DSE.");
		return -1;
	}
	if (frob_rdn(clean, entry_dn(clean), FROB_RDN_CHECK) == -1) {
		puts("Error: Old RDN not found in entry.");
		return -1;
	}
	if (frob_rdn(data, entry_dn(data), FROB_RDN_CHECK) == -1) {
		puts("Error: New RDN not found in entry.");
		return -1;
	}
	if (frob_rdn(data, entry_dn(clean), FROB_RDN_CHECK) != -1)
		*deleteoldrdn = 0;
	else if (frob_rdn(data, entry_dn(clean), FROB_RDN_CHECK_NONE) != -1)
		*deleteoldrdn = 1;
	else {
		puts("Error: Incomplete RDN change.");
		return -1;
	}
	return 0;
}
