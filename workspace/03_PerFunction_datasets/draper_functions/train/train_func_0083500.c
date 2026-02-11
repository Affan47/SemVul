notifyDocumentRecvd(FaxRecvInfo& ri)
{
    (void) sendRecvStatus(getModemDeviceID(), "D%s", (const char*) ri.encode());

    FaxServer::notifyDocumentRecvd(ri);

    FaxAcctInfo ai;
    ai.user = "fax";
    ai.commid = getCommID();
    ai.duration = (time_t) ri.time;
    ai.start = Sys::now() - ai.duration;
    ai.conntime = ai.duration;
    ai.device = getModemDeviceID();
    ai.dest = getModemNumber();
    ai.csi = ri.sender;
    ai.npages = ri.npages;
    ai.params = ri.params.encode();
    ai.status = ri.reason;
    ai.jobid = ri.qfile;
    ai.jobtag = "";
    ai.callid = ri.callid;
    ai.owner = "";
    ri.params.asciiEncode(ai.faxdcs);
    if (!ai.record("RECV"))
	logError("Error writing RECV accounting record, dest=%s",
	    (const char*) ai.dest);
}
