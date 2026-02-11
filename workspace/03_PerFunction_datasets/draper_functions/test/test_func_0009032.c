run()
{
	while (true)
	{
		if (m_abort)
			return;

		m_mutex.lock();
		Poppler::Page *pdfPage = m_tikzPdfDoc->page(m_currentPage);
		const qreal zoomFactor = m_zoomFactor;
		m_mutex.unlock();
		const QImage tikzImage = pdfPage->renderToImage(zoomFactor * 72, zoomFactor * 72);
		delete pdfPage;

		emit showPreview(tikzImage);


		m_mutex.lock();
		if (!m_restart)
			m_condition.wait(&m_mutex);
		m_restart = false;
		m_mutex.unlock();
	}
}
