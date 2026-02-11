handlePrev(int32_t position, UErrorCode &status)
{

    if (U_SUCCESS(status)) {
        if (m_strsrch_->pattern.CELength == 0) {
            m_search_->matchedIndex =
                  (m_search_->matchedIndex == USEARCH_DONE ? getOffset() :
                   m_search_->matchedIndex);
            if (m_search_->matchedIndex == 0) {
                setMatchNotFound();
            }
            else {
                m_search_->matchedIndex --;
                ucol_setOffset(m_strsrch_->textIter, m_search_->matchedIndex,
                               &status);
                m_search_->matchedLength = 0;
            }
        }
        else {


#if 0
            if (!m_search_->isOverlap &&
                position - m_strsrch_->pattern.defaultShiftSize < 0) {
                setMatchNotFound();
                return USEARCH_DONE;
            }

            for (;;) {
                if (m_search_->isCanonicalMatch) {

                    usearch_handlePreviousCanonical(m_strsrch_, &status);
                }
                else {
                    usearch_handlePreviousExact(m_strsrch_, &status);
                }
                if (U_FAILURE(status)) {
                    return USEARCH_DONE;
                }
                if (m_breakiterator_ == NULL
#if !UCONFIG_NO_BREAK_ITERATION
                    ||
                    m_search_->matchedIndex == USEARCH_DONE ||
                    (m_breakiterator_->isBoundary(m_search_->matchedIndex) &&
                     m_breakiterator_->isBoundary(m_search_->matchedIndex +
                                                  m_search_->matchedLength))
#endif
                ) {
                    return m_search_->matchedIndex;
                }
            }
#else
            ucol_setOffset(m_strsrch_->textIter, position, &status);

            if (m_search_->isCanonicalMatch) {

            	usearch_handlePreviousCanonical(m_strsrch_, &status);
            } else {
            	usearch_handlePreviousExact(m_strsrch_, &status);
            }

            if (U_FAILURE(status)) {
            	return USEARCH_DONE;
            }

            return m_search_->matchedIndex;
#endif
        }

        return m_search_->matchedIndex;
    }
    return USEARCH_DONE;
}
