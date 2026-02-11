lh_new(LHASH_HASH_FN_TYPE h, LHASH_COMP_FN_TYPE c)
	{
	_LHASH *ret;
	int i;

	if ((ret=OPENSSL_malloc(sizeof(_LHASH))) == NULL)
		goto err0;
	if ((ret->b=OPENSSL_malloc(sizeof(LHASH_NODE *)*MIN_NODES)) == NULL)
		goto err1;
	for (i=0; i<MIN_NODES; i++)
		ret->b[i]=NULL;
	ret->comp=((c == NULL)?(LHASH_COMP_FN_TYPE)strcmp:c);
	ret->hash=((h == NULL)?(LHASH_HASH_FN_TYPE)lh_strhash:h);
	ret->num_nodes=MIN_NODES/2;
	ret->num_alloc_nodes=MIN_NODES;
	ret->p=0;
	ret->pmax=MIN_NODES/2;
	ret->up_load=UP_LOAD;
	ret->down_load=DOWN_LOAD;
	ret->num_items=0;

	ret->num_expands=0;
	ret->num_expand_reallocs=0;
	ret->num_contracts=0;
	ret->num_contract_reallocs=0;
	ret->num_hash_calls=0;
	ret->num_comp_calls=0;
	ret->num_insert=0;
	ret->num_replace=0;
	ret->num_delete=0;
	ret->num_no_delete=0;
	ret->num_retrieve=0;
	ret->num_retrieve_miss=0;
	ret->num_hash_comps=0;

	ret->error=0;
	return(ret);
err1:
	OPENSSL_free(ret);
err0:
	return(NULL);
	}
