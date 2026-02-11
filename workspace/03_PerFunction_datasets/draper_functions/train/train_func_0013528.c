ENGINE_init(ENGINE *e)
	{
	int ret;
	if(e == NULL)
		{
		ENGINEerr(ENGINE_F_ENGINE_INIT,ERR_R_PASSED_NULL_PARAMETER);
		return 0;
		}
	CRYPTO_w_lock(CRYPTO_LOCK_ENGINE);
	ret = engine_unlocked_init(e);
	CRYPTO_w_unlock(CRYPTO_LOCK_ENGINE);
	return ret;
	}
