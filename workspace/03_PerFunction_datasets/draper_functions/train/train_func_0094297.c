tclhandleAlloc(tblHeader_pt headerPtr, char *handle,
			      unsigned long *entryIdxPtr)
{
    tblHeader_pt tblHdrPtr = (tblHeader_pt) headerPtr;
    entryHeader_pt entryPtr;
    int entryIdx;

    if (tblHdrPtr->freeHeadIdx == NULL_IDX)
	tclhandleExpandTable(tblHdrPtr, -1);

    entryIdx = tblHdrPtr->freeHeadIdx;
    entryPtr = TBL_INDEX(tblHdrPtr, entryIdx);
    tblHdrPtr->freeHeadIdx = entryPtr->freeLink;
    entryPtr->freeLink = ALLOCATED_IDX;

    if (handle)
	sprintf(handle, tblHdrPtr->handleFormat, entryIdx);
    if (entryIdxPtr)
	*entryIdxPtr = entryIdx;
    return USER_AREA(entryPtr);

}
