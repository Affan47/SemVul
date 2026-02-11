operator==(const SearchIterator &that) const
{
    if (this == &that) {
        return TRUE;
    }
    if (SearchIterator::operator ==(that)) {
        StringSearch &thatsrch = (StringSearch &)that;
        return (this->m_pattern_ == thatsrch.m_pattern_ &&
                this->m_strsrch_->collator == thatsrch.m_strsrch_->collator);
    }
    return FALSE;
}
