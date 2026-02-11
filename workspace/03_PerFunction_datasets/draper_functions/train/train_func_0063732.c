getMapping(int32_t index) {
    int32_t key = fKeyVec->elementAti(index);
    int32_t value = fValueVec->elementAti(index);
    int32_t length = USPOOF_KEY_LENGTH_FIELD(key);
    int32_t lastIndexWithLen;
    switch (length) {
      case 0:
        return UnicodeString(static_cast<UChar>(value));
      case 1:
      case 2:
        return UnicodeString(*fStringTable, value, length+1);
      case 3:
        length = 0;
        int32_t i;
        for (i=0; i<fStringLengthsTable->size(); i+=2) {
            lastIndexWithLen = fStringLengthsTable->elementAti(i);
            if (value <= lastIndexWithLen) {
                length = fStringLengthsTable->elementAti(i+1);
                break;
            }
        }
        U_ASSERT(length>=3);
        return UnicodeString(*fStringTable, value, length);
      default:
        U_ASSERT(FALSE);
    }
    return UnicodeString();
}
