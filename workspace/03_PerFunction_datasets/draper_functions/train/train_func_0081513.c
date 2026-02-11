assignModem(Job& job)
{
    bool retryModemLookup;
    do {
	retryModemLookup = false;
	Modem* modem = Modem::findModem(job);
	if (modem) {
	    if (modem->assign()) {
		job.modem = modem;
		Trigger::post(Trigger::MODEM_ASSIGN, *modem);
		return (true);
	    }


	    traceJob(job, "Unable to assign modem %s (cannot lock)",
		(const char*) modem->getDeviceID());
	    modem->startLockPolling(pollLockWait);
	    traceModem(*modem, "BUSY (begin polling)");
	    retryModemLookup = true;
	} else
	    traceJob(job, "No assignable modem located");
    } while (retryModemLookup);
    return (false);
}
