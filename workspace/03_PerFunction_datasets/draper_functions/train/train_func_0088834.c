add_ns(dns_db_t *db, dns_dbversion_t *version, dns_name_t *name,
       dns_name_t *nsname)
{
	dns_dbnode_t *node = NULL;
	dns_rdata_ns_t ns;
	dns_rdata_t rdata = DNS_RDATA_INIT;
	dns_rdatalist_t rdatalist;
	dns_rdataset_t rdataset;
	isc_result_t result;
	isc_buffer_t b;
	unsigned char buf[DNS_NAME_MAXWIRE];

	isc_buffer_init(&b, buf, sizeof(buf));

	dns_rdataset_init(&rdataset);
	dns_rdatalist_init(&rdatalist);
	ns.common.rdtype = dns_rdatatype_ns;
	ns.common.rdclass = dns_db_class(db);
	ns.mctx = NULL;
	dns_name_init(&ns.name, NULL);
	dns_name_clone(nsname, &ns.name);
	CHECK(dns_rdata_fromstruct(&rdata, dns_db_class(db), dns_rdatatype_ns,
				   &ns, &b));
	rdatalist.type = rdata.type;
	rdatalist.covers = 0;
	rdatalist.rdclass = rdata.rdclass;
	rdatalist.ttl = 86400;
	ISC_LIST_APPEND(rdatalist.rdata, &rdata, link);
	CHECK(dns_rdatalist_tordataset(&rdatalist, &rdataset));
	CHECK(dns_db_findnode(db, name, ISC_TRUE, &node));
	CHECK(dns_db_addrdataset(db, node, version, 0, &rdataset, 0, NULL));
 cleanup:
	if (node != NULL)
		dns_db_detachnode(db, &node);
	return (result);
}
