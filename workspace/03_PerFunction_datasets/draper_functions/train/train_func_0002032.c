IsEventCompletedByIndex(unsigned eventIndex) const
{
	ReadyEventNode *ren = readyEventNodeList[eventIndex];
	unsigned i;
	if (ren->eventStatus==ID_READY_EVENT_FORCE_ALL_SET)
		return true;
	if (ren->eventStatus!=ID_READY_EVENT_ALL_SET)
		return false;
	for (i=0; i < ren->systemList.Size(); i++)
		if (ren->systemList[i].lastReceivedStatus!=ID_READY_EVENT_ALL_SET)
			return false;
	return true;
}
