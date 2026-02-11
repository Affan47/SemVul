ENGINE_add(ENGINE *e)
	{
	int to_return = 1;
	if(e == NULL)
		{
		ENGINEerr(ENGINE_F_ENGINE_ADD,
			ERR_R_PASSED_NULL_PARAMETER);
		return 0;
		}
	if((e->id == NULL) || (e->name == NULL))
		{
		ENGINEerr(ENGINE_F_ENGINE_ADD,
			ENGINE_R_ID_OR_NAME_MISSING);
		}
	CRYPTO_w_lock(CRYPTO_LOCK_ENGINE);
	if(!engine_list_add(e))
		{
		ENGINEerr(ENGINE_F_ENGINE_ADD,
			ENGINE_R_INTERNAL_LIST_ERROR);
		to_return = 0;
		}
	CRYPTO_w_unlock(CRYPTO_LOCK_ENGINE);
	return to_return;
	}
