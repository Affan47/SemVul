SSL_SetMaxServerCacheLocks(PRUint32 maxLocks)
{


    if (maxLocks < 3) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }
    ssl_max_sid_cache_locks = maxLocks - 2;

    return SECSuccess;
}
