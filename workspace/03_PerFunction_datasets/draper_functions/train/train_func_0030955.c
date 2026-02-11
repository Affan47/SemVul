show()
{
    if ( !isTemporaryDisabled() )
    {
        QWidget::show();

        if( windowOpacity() == 0.0 && KWindowSystem::compositingActive() )
        {
            m_fadeTimeLine->setDirection( QTimeLine::Forward );
            m_fadeTimeLine->start();
        }

        else
        {
            m_fadeTimeLine->stop();
            setWindowOpacity( maxOpacity() );
        }
    }
}
