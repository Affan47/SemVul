ucnv_io_nextStandardAliases(UEnumeration *enumerator,
                            int32_t* resultLength,
                            UErrorCode * )
{
    UAliasContext *myContext = (UAliasContext *)(enumerator->context);
    uint32_t listOffset = myContext->listOffset;

    if (listOffset) {
        uint32_t listCount = gMainTable.taggedAliasLists[listOffset];
        const uint16_t *currList = gMainTable.taggedAliasLists + listOffset + 1;

        if (myContext->listIdx < listCount) {
            const char *myStr = GET_STRING(currList[myContext->listIdx++]);
            if (resultLength) {
                *resultLength = (int32_t)uprv_strlen(myStr);
            }
            return myStr;
        }
    }

    if (resultLength) {
        *resultLength = 0;
    }
    return NULL;
}
