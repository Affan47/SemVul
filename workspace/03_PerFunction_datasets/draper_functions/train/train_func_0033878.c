surewarehk_ctrl(ENGINE *e, int cmd, long i, void *p, void (*f)(void))
{
	int to_return = 1;

	switch(cmd)
	{
		case ENGINE_CTRL_SET_LOGSTREAM:
		{
			BIO *bio = (BIO *)p;
			CRYPTO_w_lock(CRYPTO_LOCK_ENGINE);
			if (logstream)
			{
				BIO_free(logstream);
				logstream = NULL;
			}
			if (CRYPTO_add(&bio->references,1,CRYPTO_LOCK_BIO) > 1)
				logstream = bio;
			else
				SUREWAREerr(SUREWARE_F_SUREWAREHK_CTRL,SUREWARE_R_BIO_WAS_FREED);
		}
		CRYPTO_w_unlock(CRYPTO_LOCK_ENGINE);
		break;


	case ENGINE_CTRL_CHIL_NO_LOCKING:
		CRYPTO_w_lock(CRYPTO_LOCK_ENGINE);
		threadsafe = 0;
		CRYPTO_w_unlock(CRYPTO_LOCK_ENGINE);
		break;


	default:
		SUREWAREerr(SUREWARE_F_SUREWAREHK_CTRL,
			ENGINE_R_CTRL_COMMAND_NOT_IMPLEMENTED);
		to_return = 0;
		break;
		}

	return to_return;
}
