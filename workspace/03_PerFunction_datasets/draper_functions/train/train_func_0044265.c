PrintBufferLeakWarning(Buffer buffer)
{
	volatile BufferDesc *buf;
	int32		loccount;
	char	   *path;

	Assert(BufferIsValid(buffer));
	if (BufferIsLocal(buffer))
	{
		buf = &LocalBufferDescriptors[-buffer - 1];
		loccount = LocalRefCount[-buffer - 1];
	}
	else
	{
		buf = &BufferDescriptors[buffer - 1];
		loccount = PrivateRefCount[buffer - 1];
	}


	path = relpath(buf->tag.rnode, buf->tag.forkNum);
	elog(WARNING,
		 "buffer refcount leak: [%03d] "
		 "(rel=%s, blockNum=%u, flags=0x%x, refcount=%u %d)",
		 buffer, path,
		 buf->tag.blockNum, buf->flags,
		 buf->refcount, loccount);
	pfree(path);
}
