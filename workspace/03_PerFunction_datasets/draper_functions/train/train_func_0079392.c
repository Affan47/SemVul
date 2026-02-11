setProcessRunning(bool isRunning)
{
	m_procStopAction->setEnabled(isRunning);
	if (isRunning)
		QApplication::setOverrideCursor(Qt::BusyCursor);
	else
		QApplication::restoreOverrideCursor();
	m_tikzPreview->setProcessRunning(isRunning);
}
