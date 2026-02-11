PopBufferedPacket(void)
{
	bufferedPacketsQueueMutex.Lock();
	if (bufferedPacketsQueue.Size()>0)
	{
		RNS2RecvStruct *s = bufferedPacketsQueue.Pop();
		bufferedPacketsQueueMutex.Unlock();
		return s;
	}
	bufferedPacketsQueueMutex.Unlock();
	return 0;
}
