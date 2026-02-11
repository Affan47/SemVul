pageEpilogue(FaxRequest& req, const FaxMachineInfo&, Status& eresult)
{
    putModem("\4\r", 2);

    fxStackBuffer buf;
    time_t start = Sys::now();
    do {
	u_int len = getResponse(buf, ixoAckTimeout);
	const u_char* cp = buf;
	while (len > 0) {
	    switch (cp[0]) {
	    case ESC:
		if (len > 1 && cp[1] == EOT) {
		    traceIXO("RECV EOT (disconnect)");
		    return (true);
		}
		break;
	    case RS:
		traceIXO("RECV RS (message content rejected)");
		eresult = Status(508, "Paging central rejected content; check PIN");
		req.status = send_failed;
		return (false);
	    }
	    (void) scanForCode(cp, len);
	}
	traceResponse(buf);

    } while ((unsigned)Sys::now() - start < ixoAckTimeout);
    req.status = send_retry;
    eresult = Status(509, "Protocol failure: timeout waiting for transaction ACK/NAK "
	"from paging central");
    return (false);
}
