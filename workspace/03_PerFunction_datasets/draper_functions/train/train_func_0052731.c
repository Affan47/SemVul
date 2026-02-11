mouseReleaseEvent( QMouseEvent * event )
{
    if( event->button() == Qt::LeftButton )
    {
        if ( m_volumeMenu->isVisible() )
            m_volumeMenu->hide();
        else
        {
            const QPoint pos( 0, height() );
            m_volumeMenu->exec( mapToGlobal( pos ) );
        }
    }
    else if( event->button() == Qt::MidButton )
    {
        The::engineController()->toggleMute();
    }

    QToolButton::mouseReleaseEvent( event );
}
