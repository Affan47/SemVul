showEvent(QShowEvent* event)
{
	if (!m_position.isNull()) {
		QRect rect(m_position, sizeHint());
		if (QApplication::desktop()->availableGeometry(this).contains(rect)) {
			move(m_position);
		}
	}
	QDialog::showEvent(event);
}
