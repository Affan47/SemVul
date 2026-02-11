notifyDocumentRecvd(FaxRecvInfo& ri)
{
    traceServer("RECV FAX (%s): %s from %s, route to %s, %u pages in %s"
	, (const char*) ri.commid
	, (const char*) ri.qfile
	, (const char*) ri.sender
	, ri.subaddr != "" ? (const char*) ri.subaddr : "<unspecified>"
	, ri.npages
	, fmtTime((time_t) ri.time)
    );
}
