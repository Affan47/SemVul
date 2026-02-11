WalRcvShutdownHandler(SIGNAL_ARGS)
{
	int			save_errno = errno;

	got_SIGTERM = true;

	SetLatch(&WalRcv->latch);


	if (!proc_exit_inprogress && WalRcvImmediateInterruptOK)
		ProcessWalRcvInterrupts();

	errno = save_errno;
}
