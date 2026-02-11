encap_hash_search(encap_hash_t *h,
			      encap_hashptr_t *hp, void *data,
			      encap_matchfunc_t matchfunc)
{
	while (encap_hash_next(h, hp) != 0)
		if ((*matchfunc)(data, encap_listptr_data(&(hp->node))) != 0)
			return 1;

	return 0;
}
