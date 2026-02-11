mousePressEvent(QMouseEvent* event)
{
    if (minimum() == maximum() || (event->buttons() ^ event->button()))
    {
        event->ignore();
        return;
    }

    qxt_d().handleMousePress(event->pos(), qxt_d().upperPressed, qxt_d().upper, QxtSpanSlider::UpperHandle);
    if (qxt_d().upperPressed != QStyle::SC_SliderHandle)
        qxt_d().handleMousePress(event->pos(), qxt_d().lowerPressed, qxt_d().lower, QxtSpanSlider::LowerHandle);

    qxt_d().firstMovement = true;
    event->accept();
}
