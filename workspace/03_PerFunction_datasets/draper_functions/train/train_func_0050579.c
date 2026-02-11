ResolveRecoveryConflictWithBufferPin(void)
{
	bool		sig_alarm_enabled = false;
	TimestampTz ltime;
	TimestampTz now;

	Assert(InHotStandby);

	ltime = GetStandbyLimitTime();
	now = GetCurrentTimestamp();

	if (!ltime)
	{


		if (enable_standby_sig_alarm(now, now, true))
			sig_alarm_enabled = true;
		else
			elog(FATAL, "could not set timer for process wakeup");
	}
	else if (now >= ltime)
	{


		SendRecoveryConflictWithBufferPin(PROCSIG_RECOVERY_CONFLICT_BUFFERPIN);
	}
	else
	{


		if (enable_standby_sig_alarm(now, ltime, false))
			sig_alarm_enabled = true;
		else
			elog(FATAL, "could not set timer for process wakeup");
	}


	ProcWaitForSignal();

	if (sig_alarm_enabled)
	{
		if (!disable_standby_sig_alarm())
			elog(FATAL, "could not disable timer for process wakeup");
	}
}
