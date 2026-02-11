compareTo(const CollationKey& target, UErrorCode &status) const
{
  if(U_SUCCESS(status)) {
    uint8_t *src = this->fBytes;
    uint8_t *tgt = target.fBytes;


    if (src == tgt)
        return  UCOL_EQUAL;

    int                         minLength;
    UCollationResult result;


    if (this->fCount != target.fCount) {
        if (this->fCount < target.fCount) {
            minLength = this->fCount;
            result    =  UCOL_LESS;
        }
        else {
            minLength = target.fCount;
            result    =  UCOL_GREATER;
        }
    }
    else {
        minLength = target.fCount;
        result    =  UCOL_EQUAL;
    }

    if (minLength > 0) {
        int diff = uprv_memcmp(src, tgt, minLength);
        if (diff > 0) {
            return UCOL_GREATER;
        }
        else
            if (diff < 0) {
                return UCOL_LESS;
            }
    }

    return result;
  } else {
    return UCOL_EQUAL;
  }
}
