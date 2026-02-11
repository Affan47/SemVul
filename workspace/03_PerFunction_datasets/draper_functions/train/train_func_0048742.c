wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QWheelEvent e(event->pos().toPoint(), event->delta(),event->buttons(),event->modifiers(),event->orientation());
    QApplication::sendEvent(widget(), &e);
    event->accept();
}
