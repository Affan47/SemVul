RecordHistory()
{


	listPOS		*ppos;
	static int	iClock;
	int		iClockPrev = iClock++;
	int		bits = (iClockPrev^iClock) & iClock;
	if (bits <= bitsHistClockMask) {
		ppos = aposRecycle;
		while ((bits /= 2) != 0)
			++ppos;

		listHR.push_back(**ppos);
		*ppos = ++listHR.erase(*ppos);
	} else {
		ppos = aposRecycle+nHistRanges-1;

		listHR.push_back(**ppos);
		*ppos = listHR.erase(*ppos);
	}


 	listPOS phr = --listHR.end();
	phr->kBytesSent = GetSessionSentBytes() / 1024.0;
	phr->kBytesReceived = GetSessionReceivedBytes() / 1024.0;
	phr->kBpsUpCur = GetUploadRate() / 1024.0;
	phr->kBpsDownCur = GetDownloadRate() / 1024.0;
	phr->cntUploads = GetActiveUploadsCount();
	phr->cntConnections = GetActiveConnections();
	phr->cntDownloads = GetDownloadingSources();
	phr->sTimestamp = GetUptimeMillis() / 1000.0;

	s_kadNodesTotal += s_kadNodesCur;
	phr->kadNodesTotal = s_kadNodesTotal;
	phr->kadNodesCur = s_kadNodesCur;

	phr->kadActiveNodesCur = s_kadActiveNodesCur;

}
