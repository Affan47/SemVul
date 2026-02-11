mouseMoveEvent(QMouseEvent *event)
{

    if ((event->pos().y() >= height() - 5 && event->pos().y() < height()) ||

            (event->pos().y() >= rect().y() && event->pos().y() < rect ().y() + 5))
    {
        setCursor(Qt::SizeVerCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
    QWidget::mouseMoveEvent(event);
}
