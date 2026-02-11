getRandomTrack() const
{
    if( !m_collection )
        return QString();

    int count = trackCount();
    if( count == 0 )
        return QString();


    int trackNr = KRandom::random() % count;
    for( int i = m_bits.size()-1; i>=0; i-- )
    {
        if( m_bits.at(i) )
        {
            if( trackNr )
                trackNr--;
            else
            {
                return m_collection->m_uids.at(i);
            }
        }
    }

    return QString();
}
