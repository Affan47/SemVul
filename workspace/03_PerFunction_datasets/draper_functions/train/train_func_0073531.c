sendPage(FaxRequest& req, FaxMachineInfo& info, u_int& batched)
{
    if (!(batched & BATCH_FIRST) || lockModem()) {
        if (batched & BATCH_FIRST) {
            beginSession(req.number);
            batchid = getCommID();
        }

        req.commid = getCommID();
        traceServer("SEND PAGE (possibly batched): JOB %s DEST %s COMMID %s DEVICE '%s'"
                    , (const char*) req.jobid
                    , (const char*) req.external
                    , (const char*) req.commid
                    , (const char*) getModemDevice()
                   );


	if (info.getPagerTTYParity() != "")
	    pagerTTYParity = info.getPagerTTYParity();

    if (!(batched & BATCH_FIRST) || setupModem(true)) {
	    changeState(SENDING);
	    setServerStatus("Sending page " | req.jobid);


	    fxStr msg;
	    if (prepareMsg(req, info, msg))
	       sendPage(req, info, prepareDialString(req.number), msg, batched);
        } else
	       sendFailed(req, send_retry, Status(422, "Can not setup modem"), 4*pollModemWait);

        if ((batched & BATCH_LAST) || (req.status != send_done)) {
            discardModem(true);
            changeState(MODEMWAIT, 5);
            unlockModem();
            endSession();
        }
    } else {
	sendFailed(req, send_retry, Status(346, "Can not lock modem device") ,2*pollLockWait);
    }
}
