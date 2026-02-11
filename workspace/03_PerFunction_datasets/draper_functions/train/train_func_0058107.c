event(QEvent* event)
{
	if (event->type() == QEvent::WindowBlocked) {
		hideInterface();
	}
	return QMainWindow::event(event);
}
