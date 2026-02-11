mouseReleaseEvent( QMouseEvent* e )
{
    if ( !m_interactive || m_tracking == NoTracking || m_image.isNull() )
        return;

    if ( !m_transform.isIdentity() ) {
        m_presenter->changePosition( m_transform );
        update();
    }

    m_tracking = NoTracking;
    m_presenter->clearTracking();

    QPointF point = worldTransform().inverted().map( e->pos() );
    m_presenter->setHoveringPoint( point );
}
