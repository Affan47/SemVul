ProcessIncomingNotify(void)
{
	bool		catchup_enabled;


	notifyInterruptOccurred = 0;


	if (listenChannels == NIL)
		return;


	catchup_enabled = DisableCatchupInterrupt();

	if (Trace_notify)
		elog(DEBUG1, "ProcessIncomingNotify");

	set_ps_display("notify interrupt", false);


	StartTransactionCommand();

	asyncQueueReadAllNotifications();

	CommitTransactionCommand();


	pq_flush();

	set_ps_display("idle", false);

	if (Trace_notify)
		elog(DEBUG1, "ProcessIncomingNotify: done");

	if (catchup_enabled)
		EnableCatchupInterrupt();
}
