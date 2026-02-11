mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPos = event->pos();
    QMenu::mousePressEvent(event);
}
