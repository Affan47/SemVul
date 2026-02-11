paintEvent(QPaintEvent* event)
{
	QFrame::paintEvent(event);

	QPainter painter(this);
	QFontMetrics metrics = painter.fontMetrics();

	QString text = metrics.elidedText(m_text, Qt::ElideRight, width());
	painter.drawText(QPoint(0, metrics.ascent()), text);
}
