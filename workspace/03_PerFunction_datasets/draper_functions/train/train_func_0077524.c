XLOGfileslop(XLogRecPtr PriorRedoPtr)
{
	XLogSegNo	minSegNo;
	XLogSegNo	maxSegNo;
	double		distance;
	XLogSegNo	recycleSegNo;


	minSegNo = PriorRedoPtr / XLOG_SEG_SIZE + min_wal_size - 1;
	maxSegNo = PriorRedoPtr / XLOG_SEG_SIZE + max_wal_size - 1;


	distance = (2.0 + CheckPointCompletionTarget) * CheckPointDistanceEstimate;

	distance *= 1.10;

	recycleSegNo = (XLogSegNo) ceil(((double) PriorRedoPtr + distance) / XLOG_SEG_SIZE);

	if (recycleSegNo < minSegNo)
		recycleSegNo = minSegNo;
	if (recycleSegNo > maxSegNo)
		recycleSegNo = maxSegNo;

	return recycleSegNo;
}
