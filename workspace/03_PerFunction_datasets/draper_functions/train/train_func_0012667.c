tclhandleFreeIndex(tblHeader_pt headerPtr, unsigned long entryIdx)
{
    tblHeader_pt tblHdrPtr = headerPtr;
    entryHeader_pt entryPtr, freeentryPtr;

    entryPtr = TBL_INDEX(tblHdrPtr, entryIdx);

    if ((entryIdx >= tblHdrPtr->tableSize) ||
	(entryPtr->freeLink != ALLOCATED_IDX)) {
	return NULL;
    }

    entryPtr = USER_AREA(entryPtr);
    freeentryPtr = HEADER_AREA(entryPtr);
    freeentryPtr->freeLink = tblHdrPtr->freeHeadIdx;
    tblHdrPtr->freeHeadIdx = (((ubyte_pt) entryPtr) - tblHdrPtr->bodyPtr) /
	tblHdrPtr->entrySize;

    return entryPtr;
}
