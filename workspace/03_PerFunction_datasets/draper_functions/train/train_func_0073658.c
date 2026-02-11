XLogFindNextRecord(XLogReaderState *state, XLogRecPtr RecPtr)
{
	XLogReaderState saved_state = *state;
	XLogRecPtr	targetPagePtr;
	XLogRecPtr	tmpRecPtr;
	int			targetRecOff;
	XLogRecPtr	found = InvalidXLogRecPtr;
	uint32		pageHeaderSize;
	XLogPageHeader header;
	XLogRecord *record;
	int			readLen;
	char	   *errormsg;

	Assert(!XLogRecPtrIsInvalid(RecPtr));

	targetRecOff = RecPtr % XLOG_BLCKSZ;


	targetPagePtr = RecPtr - targetRecOff;


	readLen = ReadPageInternal(state, targetPagePtr, targetRecOff);
	if (readLen < 0)
		goto err;

	header = (XLogPageHeader) state->readBuf;

	pageHeaderSize = XLogPageHeaderSize(header);


	readLen = ReadPageInternal(state, targetPagePtr, pageHeaderSize);
	if (readLen < 0)
		goto err;


	if (header->xlp_info & XLP_FIRST_IS_CONTRECORD)
	{

		tmpRecPtr = targetPagePtr + pageHeaderSize
			+ MAXALIGN(header->xlp_rem_len);
	}
	else
	{
		tmpRecPtr = targetPagePtr + pageHeaderSize;
	}


	while ((record = XLogReadRecord(state, tmpRecPtr, &errormsg)))
	{

		tmpRecPtr = InvalidXLogRecPtr;


		if (RecPtr <= state->ReadRecPtr)
		{
			found = state->ReadRecPtr;
			goto out;
		}
	}

err:
out:

	state->readSegNo = 0;
	state->readOff = 0;
	state->readLen = 0;
	state->ReadRecPtr = saved_state.ReadRecPtr;
	state->EndRecPtr = saved_state.EndRecPtr;

	return found;
}
