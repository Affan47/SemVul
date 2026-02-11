aclDNSLookup(DNSFilter_t * dnf, const char * dnsspec, int fqdn, const char **match)
{
    const char * subdns;
    void * table;
    Symbol_t * sym;
    int rv;

    fqdn = (fqdn) ? 1 : 0;

    if (match) *match = 0;


    if ((dnf == 0) || (dnf->dnf_hash == 0)) {

	return ACL_NOMATCH;
    }


    if (!dnsspec || !*dnsspec) {

	dnsspec = "unknown";
    }


    table = dnf->dnf_hash;


    subdns = dnsspec;

    while (subdns != 0) {


	rv = symTableFindSym(table, subdns, fqdn, (void **)&sym);
	if (rv == 0) break;


	if (subdns[0] == '.') subdns += 1;
	subdns = strchr(subdns, '.');


	fqdn = 0;
    }


    if (rv) {
	rv = symTableFindSym(table, "*", 0, (void **)&sym);
    }

    if (rv == 0) {
	if (match) *match = sym->sym_name;
	rv = ACL_DNMATCH;
    }
    else rv = ACL_NOMATCH;

    return rv;
}
