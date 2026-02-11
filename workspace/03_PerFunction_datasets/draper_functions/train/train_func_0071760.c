animateTrackLabels()
{
    bool done = true;

    int off = -m_current.label->parentWidget()->geometry().x();
    adjustLabelPos( m_prev.label, m_prev.rect.x() + off );
    m_prev.label->setOpacity( prevOpacity );
    if(done)
        done = m_prev.label->geometry().x() == m_prev.rect.x() + off;

    adjustLabelPos( m_current.label, m_current.rect.x() + off );
    if(done)
        done = m_current.label->geometry().x() == m_current.rect.x() + off;

    adjustLabelPos( m_next.label, m_next.rect.x() + off );
    m_next.label->setOpacity( nextOpacity );
    if(done)
        done = m_next.label->geometry().x() == m_next.rect.x() + off;

    adjustLabelPos( m_dummy.label, m_dummy.targetX );
    if( m_dummy.label->geometry().x() == m_dummy.targetX )
        m_dummy.label->hide();
    else
        done = false;

    if( done )
    {
        killTimer( m_trackBarAnimationTimer );
        setCurrentTrackActionsVisible( true );
        m_trackBarAnimationTimer = 0;
    }
}
