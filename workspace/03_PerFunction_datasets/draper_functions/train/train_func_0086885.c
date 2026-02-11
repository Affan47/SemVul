mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_mouseDown)
	{

		const QPointF pos = event->pos();
		const qreal dx = pos.x() - m_mouseDownPos.x(), dy = pos.y() - m_mouseDownPos.y();
		const QSizeF diamondSize = boundingRect().size();
		static const qreal draggingFuzziness = 2.0 / 3.0;
		if (qAbs(dx) > qAbs(dy))
		{
			if (qAbs(dx) >= diamondSize.width() * draggingFuzziness)
			{
				emit dragged(QPoint(dx < 0 ? -1 : 1, 0));
				m_mouseDown = false;
			}
		}
		else
		{
			if (qAbs(dy) >= diamondSize.height() * draggingFuzziness)
			{
				emit dragged(QPoint(0, dy < 0 ? -1 : 1));
				m_mouseDown = false;
			}
		}
	}
}
