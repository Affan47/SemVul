keys() const
{
    QMutexLocker locker(const_cast<QMutex *>(&m_mutex));

    QStringList list;
    for (int i = 0; i < m_plugins.count(); i++) {
        QAudioSystemPlugin* p = qobject_cast<QAudioSystemPlugin*>(m_plugins.at(i)->instance());
        if (p) list << p->keys();
    }

    return list;
}
