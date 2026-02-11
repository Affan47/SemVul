txBufInit(pTXBUFFER txBuf, uint32_t sizeInit)
{
	BC_STATUS sts = BC_STS_SUCCESS;
	int ret = 0;
	if(txBuf->buffer != NULL)
		return BC_STS_INV_ARG;
	ret = posix_memalign((void**)&txBuf->buffer, 128, sizeInit);
	if(ret)
		return BC_STS_INSUFF_RES;
	if(txBuf->buffer != NULL)
	{
		txBuf->basePointer = txBuf->buffer;
		txBuf->endPointer = txBuf->basePointer + sizeInit - 1;
		txBuf->readPointer = txBuf->writePointer = 0;
		txBuf->freeSize = txBuf->totalSize = sizeInit;
		txBuf->busySize = 0;
		pthread_mutex_init(&txBuf->flushLock, NULL);
		pthread_mutex_init(&txBuf->pushpopLock, NULL);
	}
	else
		sts = BC_STS_INSUFF_RES;
	return sts;
}
