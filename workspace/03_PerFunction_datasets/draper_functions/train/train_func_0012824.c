ucnv_io_countStandardAliases(UEnumeration *enumerator, UErrorCode * ) {
    int32_t value = 0;
    UAliasContext *myContext = (UAliasContext *)(enumerator->context);
    uint32_t listOffset = myContext->listOffset;

    if (listOffset) {
        value = gMainTable.taggedAliasLists[listOffset];
    }
    return value;
}
