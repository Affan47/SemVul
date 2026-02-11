onOcsDataFetched( int err )
{
    m_fetchCount--;
    debug()<<m_status<<"Fetch count is"<< m_fetchCount;
    if( err != 0 )
        warning() << "OCS data download failed with error"<<err;
    if( m_fetchCount == 0 )
    {
        debug()<<m_status<<"FETCH COMPLETE";
        emit switchedToOcs();
    }
}
