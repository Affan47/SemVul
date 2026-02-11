resizeEvent(QResizeEvent* event)
{
	updateMask();
	m_background = QPixmap();
	m_resize_timer->start();
	updateBackground();
	QWidget::resizeEvent(event);
}
