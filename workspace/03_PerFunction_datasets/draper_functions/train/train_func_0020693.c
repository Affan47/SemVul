addTarget(QObject *ksm)
	{
		QMutexLocker locker(&updateMutex);
		ksm->connect(this, SIGNAL(updated()), SLOT(tracker_updated()), Qt::DirectConnection);
	}
