subscribe( InfoObserver * observer )
{
    DEBUG_BLOCK;
    if( observer )
    {
        m_observers.insert( observer );
        observer->infoChanged( m_storedInfo );
    }
}
