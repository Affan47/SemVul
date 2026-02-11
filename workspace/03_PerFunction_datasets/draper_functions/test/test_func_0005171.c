lockThread()
{
	if (QThread::currentThread() == thread())
		return;

	QMetaObject::invokeMethod(this, "pauseThread", Qt::QueuedConnection);
	m_pauseSem.acquire();
}
