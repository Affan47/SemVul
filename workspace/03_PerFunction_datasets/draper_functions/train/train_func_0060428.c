post(TriggerEvent e, const QLink& tl, const QLink& any, fxStackBuffer& msg)
{
    TriggerMsgHeader& hdr = *((TriggerMsgHeader*) &msg[0]);
    hdr.length = (u_short) msg.getLength();
    hdr.event = (u_short) e;
    hdr.tstamp = Sys::now();

    u_short mask = 1<<(e&15);
    const QLink* ql;
    for (ql = tl.next; ql != &tl; ql = ql->next) {
	TriggerRef* tr = (TriggerRef*) ql;
	if (tr->ref.interests[e>>4] & mask) {
	    HylaClient& client = *tr->ref.client;
	    hdr.seqnum = client.getSeqnum();
	    client.send(msg, hdr.length);
	}
    }
    for (ql = any.next; ql != &any; ql = ql->next) {
	TriggerRef* tr = (TriggerRef*) ql;
	if (tr->ref.interests[e>>4] & mask) {
	    HylaClient& client = *tr->ref.client;
	    hdr.seqnum = client.getSeqnum();
	    client.send(msg, hdr.length);
	}
    }
}
