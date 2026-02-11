getRandom(UINT64* val)
	{
		ASSERT(val!=NULL,"VAL should be not NULL");
		if(RAND_bytes((UINT8*)val,sizeof(UINT64))!=1&&
			 RAND_pseudo_bytes((UINT8*)val,sizeof(UINT64))<0)
				return E_UNKNOWN;
		return E_SUCCESS;
	}
