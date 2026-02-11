SIGetDataEntry(SISeg *segP, int backendId,
			   SharedInvalidationMessage *data)
{
	ProcState  *stateP = &segP->procState[backendId - 1];

	if (stateP->resetState)
	{


		stateP->resetState = false;
		stateP->nextMsgNum = segP->maxMsgNum;
		return -1;
	}

	if (stateP->nextMsgNum >= segP->maxMsgNum)
		return 0;


	*data = segP->buffer[stateP->nextMsgNum % MAXNUMMESSAGES];
	stateP->nextMsgNum++;


	return 1;
}
