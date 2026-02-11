refresh(qint64 usageChange)
{
    QMutexLocker locker(&m_mutex);
    m_usage += usageChange;
    if (m_capacity <= 0 || m_usage <= m_capacity)
        return;

#ifdef QT_SAMPLECACHE_DEBUG
    qint64 recoveredSize = 0;
#endif


    for (QMap<QUrl, QSample*>::iterator it = m_samples.begin();
        it != m_samples.end();)
    {
        QSample* sample = *it;
        if (sample->m_ref > 0) {
            ++it;
            continue;
        }
#ifdef QT_SAMPLECACHE_DEBUG
        recoveredSize += sample->m_soundData.size();
#endif
        m_usage -= sample->m_soundData.size();
        sample->deleteLater();
        it = m_samples.erase(it);
        if (m_usage <= m_capacity)
            return;
    }

#ifdef QT_SAMPLECACHE_DEBUG
    qDebug() << "QSampleCache: refresh(" << usageChange
             << ") recovered size =" << recoveredSize
             << "new usage =" << m_usage;
#endif

    if (m_usage > m_capacity)
        qWarning() << "QSampleCache: usage[" << m_usage << " out of limit[" << m_capacity << "]";
}
