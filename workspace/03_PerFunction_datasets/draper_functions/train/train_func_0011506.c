slotActiveTrackChanged( const quint64 id )
{
    DEBUG_BLOCK

    doItemListsMaintenance();

    if ( currentItem() != id )
    {


        if ( ( m_historyItems.isEmpty() || m_historyItems.last() != id ) &&
             ( !m_replayedItems.contains( id ) ) )
        {
            m_historyItems.append( m_replayedItems );
            m_replayedItems.clear();
        }


        m_plannedItems.clear();


        setCurrentItem( id );
    }
}
