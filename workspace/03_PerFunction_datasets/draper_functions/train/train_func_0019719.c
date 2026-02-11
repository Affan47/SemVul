WalRcvShmemInit(void)
{
	bool		found;

	WalRcv = (WalRcvData *)
		ShmemInitStruct("Wal Receiver Ctl", WalRcvShmemSize(), &found);

	if (!found)
	{

		MemSet(WalRcv, 0, WalRcvShmemSize());
		WalRcv->walRcvState = WALRCV_STOPPED;
		SpinLockInit(&WalRcv->mutex);
	}
}
