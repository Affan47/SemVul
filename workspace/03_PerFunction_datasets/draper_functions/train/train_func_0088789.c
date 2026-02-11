StrategySyncStart(uint32 *complete_passes, uint32 *num_buf_alloc)
{
	int			result;

	LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);
	result = StrategyControl->nextVictimBuffer;
	if (complete_passes)
		*complete_passes = StrategyControl->completePasses;
	if (num_buf_alloc)
	{
		*num_buf_alloc = StrategyControl->numBufferAllocs;
		StrategyControl->numBufferAllocs = 0;
	}
	LWLockRelease(BufFreelistLock);
	return result;
}
