slotPropertiesChanged(const QString& ifaceName, const QVariantMap& changedProps, const QStringList& invalidatedProps)
{


    QMap<QString, int> changeMap;

    Q_FOREACH(const QString & key, invalidatedProps) {
        m_propertyCache.remove(key);
        changeMap.insert(key, Solid::GenericInterface::PropertyRemoved);

    }

    QMapIterator<QString, QVariant> i(changedProps);
    while (i.hasNext()) {
        i.next();
        const QString key = i.key();
        m_propertyCache.insert(key, i.value());
        changeMap.insert(key, Solid::GenericInterface::PropertyModified);

    }

    Q_EMIT propertyChanged(changeMap);
    Q_EMIT changed();
}
