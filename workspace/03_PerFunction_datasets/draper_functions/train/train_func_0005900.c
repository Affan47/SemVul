EndBatch(bool refresh)
{
    if ( m_batchCount > 0 )
    {
        m_batchCount--;
        if ( !m_batchCount && refresh )
        {
            m_batchCount++;
            AdjustScrollbars();
            m_batchCount--;
            Refresh(true);
        }
    }
}
