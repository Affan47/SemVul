ProcessStandbyReplyMessage(void)
{
	StandbyReplyMessage reply;

	pq_copymsgbytes(&reply_message, (char *) &reply, sizeof(StandbyReplyMessage));

	elog(DEBUG2, "write %X/%X flush %X/%X apply %X/%X",
		 reply.write.xlogid, reply.write.xrecoff,
		 reply.flush.xlogid, reply.flush.xrecoff,
		 reply.apply.xlogid, reply.apply.xrecoff);


	{

		volatile WalSnd *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->write = reply.write;
		walsnd->flush = reply.flush;
		walsnd->apply = reply.apply;
		SpinLockRelease(&walsnd->mutex);
	}

	SyncRepReleaseWaiters();
}
