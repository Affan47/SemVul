RegisterProperties(const QStringList &props)
{
    const QDBusMessage& msg = message();
    if (msg.service() != m_currentService) {
        watcher->removeWatchedService(m_currentService);
        m_currentService = msg.service();
        watcher->addWatchedService(m_currentService);
    }
    if (cached_props != props) {
        cached_props = props;
        QList<KimpanelProperty> list;
        foreach(const QString & prop, props) {
            list << String2Property(prop);
        }

        emit registerProperties(list);
    }
}
