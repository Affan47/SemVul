generatePreview(Poppler::Document *tikzPdfDoc, qreal zoomFactor, int currentPage)
{
	QMutexLocker locker(&m_mutex);

	m_tikzPdfDoc = tikzPdfDoc;
	m_zoomFactor = zoomFactor;
	m_currentPage = currentPage;

	if (!isRunning())
	{
		start(LowPriority);
	}
	else
	{


		m_abort = true;
		m_condition.wakeAll();
		m_abort = false;
		m_restart = true;

	}
}
