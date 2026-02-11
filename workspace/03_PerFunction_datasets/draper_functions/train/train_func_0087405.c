eventFilter( QObject *o, QEvent *e )
{
    if ( o == parentWidget() )
    {
        if ( e->type() == QEvent::Enter )
            setIcon( m_icon.image[1], 3 );
        else if ( e->type() == QEvent::Leave )
            setIcon( m_icon.image[0], 6 );
    }
    return false;
}
