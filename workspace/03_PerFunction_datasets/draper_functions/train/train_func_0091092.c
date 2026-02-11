mousePressEvent(QMouseEvent* e)
{
    QWidget* widgetUnderCursor = childAt(e->pos());
    if( widgetUnderCursor == m_timeLabelLeft ||
        widgetUnderCursor == m_timeLabelRight )
    {

        AmarokConfig::setLeftTimeDisplayRemaining( !AmarokConfig::leftTimeDisplayRemaining() );
        drawTimeDisplay( The::engineController()->trackPositionMs() );
        updateTimeLabelTooltips();
    }

    QWidget::mousePressEvent(e);
}
