StopLockPoller(cacheDesc *cache)
{
    if (!cache->poller) {
	return SECSuccess;
    }
    cache->sharedCache->stopPolling = PR_TRUE;
    if (PR_Interrupt(cache->poller) != PR_SUCCESS) {
	return SECFailure;
    }
    if (PR_JoinThread(cache->poller) != PR_SUCCESS) {
	return SECFailure;
    }
    cache->poller = NULL;
    return SECSuccess;
}
