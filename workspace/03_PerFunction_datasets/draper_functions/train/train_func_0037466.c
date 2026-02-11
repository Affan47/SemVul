mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::IBeamCursor);
    d->mState = PrivateLineEdit::FOCUSED;
    update();
    QGraphicsObject::mouseMoveEvent(event);
}
