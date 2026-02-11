operator==(
                                    const CollationElementIterator& that) const
{
    if (this == &that || m_data_ == that.m_data_) {
        return TRUE;
    }


    if (m_data_->iteratordata_.coll != that.m_data_->iteratordata_.coll)
    {
        return FALSE;
    }


    int thislength = m_data_->iteratordata_.endp -
                     m_data_->iteratordata_.string;
    int thatlength = that.m_data_->iteratordata_.endp -
                     that.m_data_->iteratordata_.string;

    if (thislength != thatlength) {
        return FALSE;
    }

    if (uprv_memcmp(m_data_->iteratordata_.string,
                    that.m_data_->iteratordata_.string,
                    thislength * U_SIZEOF_UCHAR) != 0) {
        return FALSE;
    }
    if (getOffset() != that.getOffset()) {
        return FALSE;
    }


    if ((m_data_->iteratordata_.flags & UCOL_ITER_HASLEN) == 0) {
        if ((that.m_data_->iteratordata_.flags & UCOL_ITER_HASLEN) != 0) {
            return FALSE;
        }

        if (m_data_->iteratordata_.pos
            - m_data_->iteratordata_.writableBuffer
            != that.m_data_->iteratordata_.pos
            - that.m_data_->iteratordata_.writableBuffer) {

            return FALSE;
        }
    }
    else if ((that.m_data_->iteratordata_.flags & UCOL_ITER_HASLEN) == 0) {
        return FALSE;
    }

    return (m_data_->iteratordata_.CEpos - m_data_->iteratordata_.CEs)
            == (that.m_data_->iteratordata_.CEpos
                                        - that.m_data_->iteratordata_.CEs);
}
