operator=(const SearchIterator &that)
{
    if (this != &that) {
        m_breakiterator_            = that.m_breakiterator_;
        m_text_                     = that.m_text_;
        m_search_->breakIter        = that.m_search_->breakIter;
        m_search_->isCanonicalMatch = that.m_search_->isCanonicalMatch;
        m_search_->isOverlap        = that.m_search_->isOverlap;
        m_search_->matchedIndex     = that.m_search_->matchedIndex;
        m_search_->matchedLength    = that.m_search_->matchedLength;
        m_search_->text             = that.m_search_->text;
        m_search_->textLength       = that.m_search_->textLength;
    }
    return *this;
}
