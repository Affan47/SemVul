addProgressBar( ProgressBar *childBar, QObject *owner )
{
    QMutexLocker locker( &m_mutex );

    m_progressMap.insert( owner, childBar );
    m_progressDetailsWidget->layout()->addWidget( childBar );
    if( m_progressDetailsWidget->width() < childBar->width() )
        m_progressDetailsWidget->setMinimumWidth( childBar->width() );

    m_progressDetailsWidget->setMinimumHeight( childBar->height() * m_progressMap.count()  + 8 );

    m_progressDetailsWidget->reposition();

    connect( childBar, SIGNAL(percentageChanged(int)),
            SLOT(childPercentageChanged()) );
    connect( childBar, SIGNAL(cancelled(ProgressBar*)),
            SLOT(childBarCancelled(ProgressBar*)) );
    connect( childBar, SIGNAL(complete(ProgressBar*)),
            SLOT(childBarComplete(ProgressBar*)) );
    connect( owner, SIGNAL(destroyed(QObject*)), SLOT(slotObjectDestroyed(QObject*)) );

    if( m_progressMap.count() == 1 )
    {
        setDescription( childBar->descriptionLabel()->text() );
        cancelButton()->setToolTip( i18n( "Abort" ) );
    }
    else
    {
        setDescription( i18n( "Multiple background tasks running (click to show)" ) );
        cancelButton()->setToolTip( i18n( "Abort all background tasks" ) );
    }

    cancelButton()->setHidden( false );
}
