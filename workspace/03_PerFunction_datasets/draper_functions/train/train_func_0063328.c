def_get_class(int class_index)
	{
	EX_CLASS_ITEM d, *p, *gen;
	EX_DATA_CHECK(return NULL;)
	d.class_index = class_index;
	CRYPTO_w_lock(CRYPTO_LOCK_EX_DATA);
	p = lh_EX_CLASS_ITEM_retrieve(ex_data, &d);
	if(!p)
		{
		gen = OPENSSL_malloc(sizeof(EX_CLASS_ITEM));
		if(gen)
			{
			gen->class_index = class_index;
			gen->meth_num = 0;
			gen->meth = sk_CRYPTO_EX_DATA_FUNCS_new_null();
			if(!gen->meth)
				OPENSSL_free(gen);
			else
				{


				(void)lh_EX_CLASS_ITEM_insert(ex_data, gen);
				p = gen;
				}
			}
		}
	CRYPTO_w_unlock(CRYPTO_LOCK_EX_DATA);
	if(!p)
		CRYPTOerr(CRYPTO_F_DEF_GET_CLASS,ERR_R_MALLOC_FAILURE);
	return p;
	}
