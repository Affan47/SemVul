timerEvent(QTimerEvent *event)
{

    if (event->timerId() != timerId) {
        QObject::timerEvent(event);
        return;
    }

    killTimer(timerId);
    timerId = 0;


    const QPoint &mousePos = QCursor::pos();
    if (hoverPoint == mousePos)
        showToolTip(hoverPoint);
}
