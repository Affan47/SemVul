setReordering(const int32_t *codes, int32_t length, const uint8_t table[256]) {
    if(length == 0) {
        resetReordering();
    } else {
        uint8_t *ownedTable;
        int32_t *ownedCodes;
        if(length <= reorderCodesCapacity) {
            ownedTable = const_cast<uint8_t *>(reorderTable);
            ownedCodes = const_cast<int32_t *>(reorderCodes);
        } else {

            int32_t capacity = (length + 3) & ~3;
            uint8_t *bytes = (uint8_t *)uprv_malloc(256 + capacity * 4);
            if(bytes == NULL) { return FALSE; }
            if(reorderCodesCapacity != 0) {
                uprv_free(const_cast<int32_t *>(reorderCodes));
            }
            reorderTable = ownedTable = bytes + capacity * 4;
            reorderCodes = ownedCodes = (int32_t *)bytes;
            reorderCodesCapacity = capacity;
        }
        uprv_memcpy(ownedTable, table, 256);
        uprv_memcpy(ownedCodes, codes, length * 4);
        reorderCodesLength = length;
    }
    return TRUE;
}
