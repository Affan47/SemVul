mouseMoveEvent( QMouseEvent *me )
{
    if ( me->buttons() == Qt::NoButton )
        setCursor( onRing( rect(), me->pos() ) ? Qt::PointingHandCursor : Qt::ArrowCursor );
    else if ( m_isClick )
        me->accept();
    else
        QDial::mouseMoveEvent( me );
}
