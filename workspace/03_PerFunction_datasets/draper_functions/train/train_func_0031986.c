mouseMoveEvent(QGraphicsSceneMouseEvent * event) {
    if (!m_dragTerminalPoint) return;

    if (ShiftDown && !(event->modifiers() & Qt::ShiftModifier)) {
		ShiftDown = false;
	}
	QPointF p = event->pos();
	if (ShiftDown) {
		if (ShiftX) {

			p.setY(OriginalShiftPos.y());
		}
		else if (ShiftY) {

			p.setX(OriginalShiftPos.x());
		}
        else {
            double dx = qAbs(p.x() - OriginalShiftPos.x());
            double dy = qAbs(p.y() - OriginalShiftPos.y());
            if (dx - dy > MinMouseMove) {
                ShiftX = true;
            }
            else if (dy - dx > MinMouseMove) {
                ShiftY = true;
            }
        }
	}
	else if (event->modifiers() & Qt::ShiftModifier) {
		ShiftDown = true;
        ShiftX = ShiftY = false;
        OriginalShiftPos = event->pos();
	}


    QPointF newTerminalPoint = m_terminalPointOrigin + p - m_dragTerminalOrigin;
    if (newTerminalPoint.x() < 0) newTerminalPoint.setX(0);
    else if (newTerminalPoint.x() > rect().width()) newTerminalPoint.setX(rect().width());
    if (newTerminalPoint.y() < 0) newTerminalPoint.setY(0);
    else if (newTerminalPoint.y() > rect().height()) newTerminalPoint.setY(rect().height());
    m_terminalPoint = newTerminalPoint;
    emit terminalPointMoved(this, newTerminalPoint);
    update();
}
