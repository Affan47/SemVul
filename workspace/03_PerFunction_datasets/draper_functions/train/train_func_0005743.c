bottomModelRowsInserted( const QModelIndex& parent, int start, int end )
{
    Q_UNUSED( parent )
    Q_UNUSED( end )


    if( m_rowsInsertedScrollItem == 0 && !AmarokConfig::dynamicMode() )
    {
        m_rowsInsertedScrollItem = Playlist::ModelStack::instance()->bottom()->idAt( start );
        QTimer::singleShot( 0, this, SLOT(bottomModelRowsInsertedScroll()) );
    }
}
