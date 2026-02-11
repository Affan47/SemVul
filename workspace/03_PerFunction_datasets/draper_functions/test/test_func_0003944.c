setGameCaption()
{
    QString caption;
    if ( m_dealer )
    {
        const DealerInfo * di = m_dealer_map.value( m_dealer->gameId() );
        caption = QString("%1 - %2").arg( di->baseName() ).arg(m_dealer->gameNumber());
    }
    setCaption( caption );
}
