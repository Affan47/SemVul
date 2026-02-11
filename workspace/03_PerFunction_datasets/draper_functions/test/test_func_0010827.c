qcCheck() const
{
    for(size_t i = 0; i < m_rootSeq.size(); ++i)
    {
        AlphaCount64 ac = getAlphaCount(i);
        size_t callSupport = ac.get(m_rootSeq[i]);
        if(callSupport < 2)
            return false;
    }
    return true;
}
