setVisible( bool visible )
{
    if ( visible )
    {
        if ( !isEnabled() || m_text.isEmpty() )
            return;

        const uint margin = fontMetrics().width( 'x' );

        const QRect newGeometry = determineMetrics( margin );

        if( newGeometry.width() > 0 && newGeometry.height() > 0 )
        {
            m_margin = margin;
            m_size = newGeometry.size();
            setGeometry( newGeometry );
            QWidget::setVisible( visible );

            if( m_duration )
                m_timer->start( m_duration );
        }
        else
            warning() << "Attempted to make an invalid sized OSD\n";

        update();
    }
    else
        QWidget::setVisible( visible );
}
