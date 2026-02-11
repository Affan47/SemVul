triggerEvent(const TriggerMsgHeader& h, const char* cp)
{
#define	EventType(e)	((e)>>4)
    int evt = EventType(h.event);
    if (evt == EventType(JOB_BASE) || evt == EventType(SEND_BASE)) {
	JobExt job;
	cp = job.decode(cp);


	fxStr emsg;
	Job* jp = findJob(job.jobid, emsg);
	if (jp) {
	    jp->tts = job.tts;
	    jp->killtime = job.killtime;
	    jp->state = job.state;
	    jp->pri = job.pri;
	    jp->commid = job.commid;
	}
	if (IS(LOGTRIG) && type == TYPE_A) {
	    if (evt == EventType(JOB_BASE))
		logJobEventMsg(h, job);
	    else
		logSendEventMsg(h, job, cp);
	}
    } else if (evt == EventType(MODEM_BASE) || evt == EventType(RECV_BASE)) {
	ModemExt modem;
	cp = modem.decode(cp);

	if (evt == EventType(RECV_BASE))
	{
	    FaxRecvInfo ri;
	    ri.decode(cp);


	    RecvInfo* rip = recvq[ri.qfile];
	    if (!rip)
		recvq[ri.qfile] = rip = new RecvInfo(ri.qfile);
	    if (rip->recvTime == 0)
		rip->recvTime = h.tstamp;
	    if (h.event == Trigger::RECV_END) {
		rip->beingReceived = false;
		rip->reason = ri.reason;
	    } else
		rip->beingReceived = true;
	    rip->sender = ri.sender;
	    rip->subaddr = ri.subaddr;
	    rip->npages = ri.npages;
	    rip->time = h.tstamp - rip->recvTime;
	    rip->commid = ri.commid;
	    if (IS(LOGTRIG) && type == TYPE_A)
		logRecvEventMsg(h, ri, cp);
	} else if (IS(LOGTRIG) && type == TYPE_A)
	    logModemEventMsg(h, modem, cp);
    } else {
	logError("Unrecognized trigger event message %u.", h.event);
	return;
    }
    if (IS(LOGTRIG) && type == TYPE_I) {


	(void) Sys::write(data, cp - sizeof (h), h.length);
    }
#undef EventType
}
