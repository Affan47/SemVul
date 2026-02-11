LockBuffer(Buffer buffer, int mode)
{
	volatile BufferDesc *buf;

	Assert(BufferIsValid(buffer));
	if (BufferIsLocal(buffer))
		return;

	buf = &(BufferDescriptors[buffer - 1]);

	if (mode == BUFFER_LOCK_UNLOCK)
		LWLockRelease(buf->content_lock);
	else if (mode == BUFFER_LOCK_SHARE)
		LWLockAcquire(buf->content_lock, LW_SHARED);
	else if (mode == BUFFER_LOCK_EXCLUSIVE)
		LWLockAcquire(buf->content_lock, LW_EXCLUSIVE);
	else
		elog(ERROR, "unrecognized buffer lock mode: %d", mode);
}
