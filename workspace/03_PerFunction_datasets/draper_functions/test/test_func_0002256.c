t1_search(char *name, dns_rbt_t *rbt, isc_mem_t *mctx,
	  isc_result_t *dns_result)
{
	int		nprobs;
	dns_name_t	*dns_searchname;
	dns_name_t	*dns_foundname;
	dns_fixedname_t	dns_fixedname;
	void		*data;

	nprobs = 0;
	if (name && dns_result) {
		if (create_name(name, mctx, &dns_searchname) == 0) {
			dns_fixedname_init(&dns_fixedname);
			dns_foundname = dns_fixedname_name(&dns_fixedname);
			data = NULL;
			*dns_result = dns_rbt_findname(rbt, dns_searchname, 0,
						dns_foundname, &data);
			delete_name(dns_searchname, mctx);
		} else {
			++nprobs;
		}
	} else {
		++nprobs;
	}
	return(nprobs);
}
