sdt_push(SDatTable *sdt, char *dn, char *uid)
{
    char **sddns, **sddns0;
    char **sduids;

    if (!dn && !uid)
	return sdt->size;

    if (sdt->size >= sdt->capacity) {

	sdt->capacity += SDT_STEP;
	sddns = (char **)realloc(sdt->dns, sizeof(char *) * sdt->capacity);
	if (!sddns) return 0;
	sddns0 = sdt->dns;
	sdt->dns = sddns;
	sduids = (char **)realloc(sdt->uids, sizeof(char *) * sdt->capacity);
	if (!sduids) {
	    sdt->dns = sddns0;
	    return 0;
	}
	sdt->uids = sduids;
    }

    sdt->dns[sdt->size] = dn;
    sdt->uids[sdt->size] = uid;
    return ++sdt->size;
}
