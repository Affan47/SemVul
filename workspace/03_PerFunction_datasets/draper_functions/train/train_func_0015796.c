next(UErrorCode &status)
{
    if (U_SUCCESS(status)) {
        int32_t offset = getOffset();
        int32_t matchindex  = m_search_->matchedIndex;
        int32_t     matchlength = m_search_->matchedLength;
        m_search_->reset = FALSE;
        if (m_search_->isForwardSearching == TRUE) {
            int32_t textlength = m_search_->textLength;
            if (offset == textlength || matchindex == textlength ||
                (matchindex != USEARCH_DONE &&
                matchindex + matchlength >= textlength)) {

                setMatchNotFound();
                return USEARCH_DONE;
            }
        }
        else {


            m_search_->isForwardSearching = TRUE;
            if (m_search_->matchedIndex != USEARCH_DONE) {


                return matchindex;
            }
        }

        if (matchlength > 0) {

            if (m_search_->isOverlap) {
                offset ++;
            }
            else {
                offset += matchlength;
            }
        }
        return handleNext(offset, status);
    }
    return USEARCH_DONE;
}
