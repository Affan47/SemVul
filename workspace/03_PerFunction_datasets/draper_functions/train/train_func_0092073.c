AddValueByObjectID(uint64_t objectId, RakString key, SHValueType val, Time curTime, bool combineEqualTimes)
{
	unsigned int idx = GetObjectIndex(objectId);
	if (idx == (unsigned int) -1)
		return false;
	AddValueByIndex(idx, key, val, curTime, combineEqualTimes);
	return true;
}
