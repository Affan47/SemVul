seek(int64_t offset)
{
    off_t cur = offset - pos();
    if (cur == 0)
        return offset;
    if (cur <= m_iBuffered && -cur <= m_iPos)
	return seekCur(cur);

    m_iBuffered = m_iPos = 0;
    m_bEof = false;
    return lseek64(m_iFd, offset, SEEK_SET);
}
