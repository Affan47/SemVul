resize(int32_t appendLength, UErrorCode &errorCode) {
    int32_t reorderStartIndex=(int32_t)(reorderStart-start);
    int32_t length=(int32_t)(limit-start);
    str.releaseBuffer(length);
    int32_t newCapacity=length+appendLength;
    int32_t doubleCapacity=2*str.getCapacity();
    if(newCapacity<doubleCapacity) {
        newCapacity=doubleCapacity;
    }
    if(newCapacity<256) {
        newCapacity=256;
    }
    start=str.getBuffer(newCapacity);
    if(start==NULL) {

        errorCode=U_MEMORY_ALLOCATION_ERROR;
        return FALSE;
    }
    reorderStart=start+reorderStartIndex;
    limit=start+length;
    remainingCapacity=str.getCapacity()-length;
    return TRUE;
}
