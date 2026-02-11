GetRedoRecPtr(void)
{
	XLogRecPtr	ptr;


	SpinLockAcquire(&XLogCtl->info_lck);
	ptr = XLogCtl->RedoRecPtr;
	SpinLockRelease(&XLogCtl->info_lck);

	if (RedoRecPtr < ptr)
		RedoRecPtr = ptr;

	return RedoRecPtr;
}
