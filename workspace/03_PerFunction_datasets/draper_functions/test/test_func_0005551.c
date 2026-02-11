vacm_scanGroupNext(void)
{
    struct vacm_groupEntry *returnval = groupScanPtr;
    if (groupScanPtr)
        groupScanPtr = groupScanPtr->next;
    return returnval;
}
