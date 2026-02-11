mousePressEvent( QMouseEvent *e )
{
    if ( d->m_dragEnabled )
        d->startPos = e->pos();
    QPushButton::mousePressEvent( e );
}
